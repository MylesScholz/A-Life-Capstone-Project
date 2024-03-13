#include "flagella.hpp"

void Flagella::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_movement_force_vector", "movement_force_vector"), &Flagella::setMovementForceVector);
	ClassDB::bind_method(D_METHOD("get_movement_force_vector"), &Flagella::getMovementForceVector);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::VECTOR2, "movement_force_vector"), "set_movement_force_vector", "get_movement_force_vector");

	ClassDB::bind_method(D_METHOD("set_position_vector", "position_vector"), &Flagella::setPositionVector);
	ClassDB::bind_method(D_METHOD("get_position_vector"), &Flagella::getPositionVector);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::VECTOR2, "position_vector"), "set_position_vector", "get_position_vector");

	ClassDB::bind_method(D_METHOD("set_activation_energy_cost", "activation_energy_cost"), &Flagella::setActivationEnergyCost);
	ClassDB::bind_method(D_METHOD("get_activation_energy_cost"), &Flagella::getActivationEnergyCost);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::FLOAT, "activation_energy_cost"), "set_activation_energy_cost", "get_activation_energy_cost");

	ClassDB::bind_method(D_METHOD("set_activation_energy_threshold", "activation_energy_threshold"), &Flagella::setActivationEnergyThreshold);
	ClassDB::bind_method(D_METHOD("get_activation_energy_threshold"), &Flagella::getActivationEnergyThreshold);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::FLOAT, "activation_energy_threshold"), "set_activation_energy_threshold", "get_activation_energy_threshold");
}

Flagella::Flagella() {
	// CellStructure attributes
	this->setCreationNutrientCost(10.0);
	this->setMaintenanceNutrientCost(1.0);
	this->setCreationEnergyCost(10.0);
	this->setMaintenanceEnergyCost(1.0);

	// Flagella attributes
	_movementForceVector = Vector2(0, 1);
	_positionVector = Vector2();
	_activationEnergyCost = 1.0;
	_activationEnergyThreshold = 1.0;

	rand.instantiate();
}
Flagella::~Flagella() {}

void Flagella::activate(CellState *cellState) {
	bool thresholdCondition = false;

	if (cellState->getTotalEnergy() >= _activationEnergyCost) {
		thresholdCondition = cellState->getTotalEnergy() / cellState->getEnergyMaximum() >= _activationEnergyThreshold;
	}

	if (thresholdCondition) {
		float direction = rand->randf_range(0, 2 * Math_PI);
		Vector2 force = _movementForceVector.rotated(direction);

		cellState->setNextMovementVector(force);
		cellState->incrementTotalEnergy(-_activationEnergyCost);

		// UtilityFunctions::print("Flagella activated: (", force.x, ", ", force.y, ")");
	} else {
		cellState->setNextMovementVector(Vector2(0, 0));
	}
}

void Flagella::modify(String modName, float modValue) {
	//Turns out Godot Strings hate switches
	if (modName == "Strength") {
		setMovementForceVector(getMovementForceVector() * modValue); //Example
	} else if (modName == "Efficiency") {
	} else if (modName == "FlagellaPlacement") {
	}
}

void Flagella::setMovementForceVector(const Vector2 movementForceVector) { _movementForceVector = movementForceVector; }
Vector2 Flagella::getMovementForceVector() const { return _movementForceVector; }

void Flagella::setPositionVector(const Vector2 positionVector) { _positionVector = positionVector; }
Vector2 Flagella::getPositionVector() const { return _positionVector; }

void Flagella::setActivationEnergyCost(const float activationEnergyCost) { _activationEnergyCost = activationEnergyCost; }
float Flagella::getActivationEnergyCost() const { return _activationEnergyCost; }

void Flagella::setActivationEnergyThreshold(const float activationEnergyThreshold) { _activationEnergyThreshold = activationEnergyThreshold; }
float Flagella::getActivationEnergyThreshold() const { return _activationEnergyThreshold; }

void Flagella::_ready() {
	Sprite2D *sprite = this->get_node<Sprite2D>("Sprite2D");
	if (sprite)
		this->setSprite(sprite);
}