#include "cell_membrane.hpp"

void CellMembrane::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_receptor_activated", "receptor"), &CellMembrane::_on_receptor_activated);
	ClassDB::bind_method(D_METHOD("_on_receptor_deactivated", "receptor"), &CellMembrane::_on_receptor_deactivated);

	ADD_SIGNAL(MethodInfo("receptor_activated", PropertyInfo(Variant::OBJECT, "receptor")));
	ADD_SIGNAL(MethodInfo("receptor_deactivated", PropertyInfo(Variant::OBJECT, "receptor")));
}

CellMembrane::CellMembrane() {
	_receptors = Vector<Receptor *>();
	_activatedReceptors = Vector<Receptor *>();
}
CellMembrane::~CellMembrane() {
	queue_free();
}

void CellMembrane::activate(CellState *cellState) {
	// UtilityFunctions::print("CellMembrane._activatedReceptors: ");
	// for (Receptor *receptor : _activatedReceptors) {
	// 	UtilityFunctions::print("    (", receptor->get_position().x, ", ", receptor->get_position().y, ")");
	// }
}
void CellMembrane::_on_receptor_activated(Receptor *receptor) {
	// UtilityFunctions::print("CellMembrane received 'receptor_activated': (", receptor->get_position().x, ", ", receptor->get_position().y, ")");
	int index = _activatedReceptors.find(receptor);
	if (index < 0)
		_activatedReceptors.push_back(receptor);
}
void CellMembrane::_on_receptor_deactivated(Receptor *receptor) {
	// UtilityFunctions::print("CellMembrane received 'receptor_deactivated': (", receptor->get_position().x, ", ", receptor->get_position().y, ")");
	int index = _activatedReceptors.find(receptor);
	if (index >= 0)
		_activatedReceptors.remove_at(index);
}

Vector<Receptor *> CellMembrane::getReceptors() { return _receptors; }
void CellMembrane::createReceptor() {
	Ref<PackedScene> receptorScene = ResourceLoader::get_singleton()->load("res://receptor.tscn");
	Receptor *receptor = Object::cast_to<Receptor>(receptorScene->instantiate());
	_receptors.push_back(receptor);
	this->add_child(receptor);
	receptor->connect("receptor_activated", Callable(this, "_on_receptor_activated"));
	receptor->connect("receptor_deactivated", Callable(this, "_on_receptor_deactivated"));
	receptor->getSprite()->apply_scale(Vector2(this->getScale(), this->getScale()));

	Vector2 receptorInitialPosition = Vector2(0, 52 * this->getScale());
	float receptorRotationAngle = 2 * Math_PI / _receptors.size();
	for (int i = 0; i < _receptors.size(); i++) {
		_receptors[i]->set_position(receptorInitialPosition.rotated(i * receptorRotationAngle));
		_receptors[i]->set_rotation(i * receptorRotationAngle);
	}
}
void CellMembrane::removeReceptor() {
	Receptor *removedReceptor = _receptors[_receptors.size() - 1];
	_receptors.remove_at(_receptors.size() - 1);
	this->remove_child(removedReceptor);
}

Vector<Receptor *> CellMembrane::getActivatedReceptors() { return _activatedReceptors; }

void CellMembrane::_ready() {
	Sprite2D *sprite = this->get_node<Sprite2D>("Sprite2D");
	if (sprite)
		this->setSprite(sprite);

	this->createReceptor();
	this->createReceptor();
	this->createReceptor();
	this->createReceptor();
	this->createReceptor();
	this->createReceptor();
}