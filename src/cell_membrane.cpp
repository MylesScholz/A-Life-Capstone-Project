#include "cell_membrane.hpp"

void CellMembrane::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_receptor_activated", "receptor"), &CellMembrane::_on_receptor_activated);
	ClassDB::bind_method(D_METHOD("_on_receptor_deactivated", "receptor"), &CellMembrane::_on_receptor_deactivated);

	ADD_SIGNAL(MethodInfo("receptor_activated", PropertyInfo(Variant::OBJECT, "receptor")));
	ADD_SIGNAL(MethodInfo("receptor_deactivated", PropertyInfo(Variant::OBJECT, "receptor")));
}

CellMembrane::CellMembrane() {
	_nReceptors = 0.0;
	_receptors = Vector<Receptor *>();
	_activatedReceptors = Vector<Receptor *>();
}
CellMembrane::~CellMembrane() {
	queue_free();
}

void CellMembrane::activate(CellState *cellState) {
	Vector<Vector2> receptorVectors = Vector<Vector2>();

	// Add the position vector of each activated receptor to a new list
	for (Receptor *receptor : _activatedReceptors) {
		receptorVectors.push_back(receptor->get_position());
	}

	// Update the cell state with the list of position vectors of activated receptors
	cellState->setReceptorVectors(receptorVectors);
}
void CellMembrane::modify(String modifierName, float modifierValue) {
	/*
	 * Relevant ModifierGenes
	 * N_SUBSTRUCTURES: creates given number of Receptors
	 */

	if (modifierName == "N_SUBSTRUCTURES") {
		setNReceptors(modifierValue);
	}
}

void CellMembrane::applyScale(const float scale) {
	CellStructure::applyScale(scale);

	_rearrangeReceptors();
}

void CellMembrane::_on_receptor_activated(Receptor *receptor) {
	// Check if the receptor is already activated
	int index = _activatedReceptors.find(receptor);
	if (index < 0)
		// If not, add the receptor to the local list of activated receptors
		_activatedReceptors.push_back(receptor);
}
void CellMembrane::_on_receptor_deactivated(Receptor *receptor) {
	// Find the receptor in the local list of activated receptors
	int index = _activatedReceptors.find(receptor);
	if (index >= 0)
		// If found, remove the receptor
		_activatedReceptors.remove_at(index);
}

void CellMembrane::setNReceptors(const int nReceptors) {
	if (nReceptors >= 0 && nReceptors <= 10) {
		_nReceptors = nReceptors;
		_updateReceptors();
	}
}
int CellMembrane::getNReceptors() const { return _nReceptors; }

Vector<Receptor *> CellMembrane::getReceptors() { return _receptors; }
Vector<Receptor *> CellMembrane::getActivatedReceptors() { return _activatedReceptors; }

void CellMembrane::_ready() {
	Sprite2D *sprite = this->get_node<Sprite2D>("Sprite2D");
	if (sprite)
		this->setSprite(sprite);

	_updateReceptors();
}

void CellMembrane::_rearrangeReceptors() {
	// Set the default receptor position ("top" of the cell, on the edge)
	Vector2 receptorInitialPosition = Vector2(0, 52 * this->getScale());
	// Calculate the rotation increment
	float receptorRotationAngle = 2 * Math_PI / _receptors.size();

	// For each receptor, position it by rotating it incrementally counterclockwise from the default position
	for (int i = 0; i < _receptors.size(); i++) {
		_receptors[i]->set_position(receptorInitialPosition.rotated(i * receptorRotationAngle));
		_receptors[i]->set_rotation(i * receptorRotationAngle);
		_receptors[i]->setScale(this->getScale());
	}
}

void CellMembrane::_createReceptor() {
	// Load the receptor scene from its file
	Ref<PackedScene> receptorScene = ResourceLoader::get_singleton()->load("res://receptor.tscn");
	// Instantiate the scene and cast it to a Receptor object
	Receptor *receptor = Object::cast_to<Receptor>(receptorScene->instantiate());
	// Add the Receptor to _receptors and as a child node of this CellMembrane
	_receptors.push_back(receptor);
	this->add_child(receptor);

	// Connect the new Receptor's activation/deactivation signals to this CellMembrane's callback functions
	receptor->connect("receptor_activated", Callable(this, "_on_receptor_activated"));
	receptor->connect("receptor_deactivated", Callable(this, "_on_receptor_deactivated"));
}
void CellMembrane::_createReceptors(const int nReceptors) {
	// Check limits on the number of receptors
	if (nReceptors < 1 || nReceptors + _receptors.size() > 10)
		return;

	// Create each receptor
	for (int i = 0; i < nReceptors; i++) {
		_createReceptor();
	}

	// Update the positions of the receptors to accommodate the new receptors
	_rearrangeReceptors();
}
void CellMembrane::_removeReceptor() {
	// Only attempt to remove a receptor if there is at least one
	if (_receptors.size() < 1)
		return;

	// Get the last receptor in _receptors
	Receptor *removedReceptor = _receptors[_receptors.size() - 1];
	// Remove the last receptor from _receptors
	_receptors.remove_at(_receptors.size() - 1);
	// Remove the receptor from the node hierarchy
	this->remove_child(removedReceptor);
}
void CellMembrane::_removeReceptors(const int nReceptors) {
	// Check limits on the number of receptors
	if (nReceptors < 1 || nReceptors > _receptors.size())
		return;

	// Remove the given number of receptors
	for (int i = 0; i < nReceptors; i++) {
		_removeReceptor();
	}

	// Update the positions of the remaining receptors (if any)
	_rearrangeReceptors();
}

void CellMembrane::_updateReceptors() {
	if (_nReceptors > _receptors.size())
		_createReceptors(_nReceptors - _receptors.size());
	else if (_nReceptors < _receptors.size())
		_removeReceptors(_receptors.size() - _nReceptors);
}