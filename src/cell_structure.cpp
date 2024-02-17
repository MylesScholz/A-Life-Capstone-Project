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
