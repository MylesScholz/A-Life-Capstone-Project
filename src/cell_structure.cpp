#include "cell_structure.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

void CellStructure::_bind_methods() {}

CellStructure::CellStructure() {}
CellStructure::~CellStructure() {}

void CellStructure::activate(CellState *) {
	// UtilityFunctions::print("CellStructure::activate()");
}

void CellStructure::modify(String, float) {
}

void CellStructure::applyScale(const float scale) {
	if (scale <= 0)
		return;

	_sprite = this->get_node<Sprite2D>("Sprite2D");
	if (_sprite) {
		_sprite->apply_scale(Vector2(scale, scale));
		Vector2 offset = _sprite->get_position();
		_sprite->set_position(offset * scale);
	}
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

void CellStructure::setSprite(Sprite2D *sprite) { _sprite = sprite; }
Sprite2D *CellStructure::getSprite() { return _sprite; }
