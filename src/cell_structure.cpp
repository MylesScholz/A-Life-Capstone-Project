#include "cell_structure.hpp"

void CellStructure::_bind_methods() {}

CellStructure::CellStructure() {
	_scale = 1.0;
}
CellStructure::~CellStructure() {}

void CellStructure::activate(CellState *) {
	// UtilityFunctions::print("CellStructure::activate()");
}
void CellStructure::modify(String, float) {
}
void CellStructure::applyScale(const float scale) {
	if (scale <= 0)
		return;

	_sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (_sprite) {
		_sprite->apply_scale(Vector2(scale, scale));
		Vector2 offset = _sprite->get_position();
		_sprite->set_position(offset * scale);
	}

	_scale *= scale;
}

void CellStructure::setCreationNutrientCost(const float creationNutrientCost) {
	if (creationNutrientCost > 0)
		_creationNutrientCost = creationNutrientCost;
}
float CellStructure::getCreationNutrientCost() const { return _creationNutrientCost; }

void CellStructure::setMaintenanceNutrientCost(const float maintenanceNutrientCost) {
	if (maintenanceNutrientCost > 0)
		_maintenanceNutrientCost = maintenanceNutrientCost;
}
float CellStructure::getMaintenanceNutrientCost() const { return _maintenanceNutrientCost; }

void CellStructure::setCreationEnergyCost(const float creationEnergyCost) {
	if (creationEnergyCost > 0)
		_creationEnergyCost = creationEnergyCost;
}
float CellStructure::getCreationEnergyCost() const { return _creationEnergyCost; }

void CellStructure::setMaintenanceEnergyCost(const float maintenanceEnergyCost) {
	if (maintenanceEnergyCost > 0)
		_maintenanceEnergyCost = maintenanceEnergyCost;
}
float CellStructure::getMaintenanceEnergyCost() const { return _maintenanceEnergyCost; }

float CellStructure::getScale() const { return _scale; }

void CellStructure::setSprite(AnimatedSprite2D *sprite) { _sprite = sprite; }
AnimatedSprite2D *CellStructure::getSprite() { return _sprite; }
Size2 CellStructure::getSpriteSize() {
	if (_sprite)
		return _sprite->get_sprite_frames()->get_frame_texture("activate", 0)->get_size();
}
