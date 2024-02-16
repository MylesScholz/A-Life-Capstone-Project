#include "cell_structure.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

void CellStructure::_bind_methods() {}

CellStructure::CellStructure() {}
CellStructure::~CellStructure() {}

void CellStructure::activate(CellState *) {
	// UtilityFunctions::print("CellStructure::activate()");
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
