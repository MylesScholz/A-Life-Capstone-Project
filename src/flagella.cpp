#include "flagella.hpp"

using namespace godot;

void Flagella::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_movement_force", "movement_force"), &Flagella::setMovementForceVector);
	ClassDB::bind_method(D_METHOD("get_movement_force"), &Flagella::getMovementForceVector);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::VECTOR2, "movement_force"), "set_movement_force", "get_movement_force");

	ClassDB::bind_method(D_METHOD("set_position_vector", "position_vector"), &Flagella::setPositionVector);
	ClassDB::bind_method(D_METHOD("get_position_vector"), &Flagella::getPositionVector);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::VECTOR2, "position_vector"), "set_position_vector", "get_posiion_vector");

	ClassDB::bind_method(D_METHOD("set_activation_energy_cost", "activation_energy_cost"), &Flagella::setActivationEnergyCost);
	ClassDB::bind_method(D_METHOD("get_activation_energy_cost"), &Flagella::getActivationEnergyCost);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::VECTOR2, "activation_energy_cost"), "set_activation_energy_cost", "get_activation_energy_cost");
}

Flagella::Flagella() {
	_movementForceVector = Vector2();
	_positionVector = Vector2();
	_activationEnergyCost = 1.0;
	_activationEnergyThreshold = 1.0;
}
Flagella::~Flagella() {}

void Flagella::activate(CellState *cellState) {
	bool thresholdCondition = false;

	if (cellState->getTotalEnergy() >= _activationEnergyCost) { //implement movement energy cost threshold
		thresholdCondition = cellState->getTotalEnergy() / cellState->getEnergyMaximum() >= _activationEnergyThreshold;
	}

	if (thresholdCondition) {
		float force_magnitude = rand->randf_range(0, 10);
		float direction = rand->randf_range(0, 2 * Math_PI);
		Vector2 force = Vector(0, -1).rotated(direction) * force_magnitude;
		cellState->setNextMovementVector(force);
		cellState->incrementTotalEnergy(-_activationEnergyCost);
	}
}

void Flagella::setMovementForceVector(const Vector2 movementForceVector) { _movementForceVector = movementForceVector; }
Vector2 Flagella::getMovementForceVector() const { return _movementForceVector; }

void Flagella::setPositionVector(const Vector2 positionVector) { _positionVector = positionVector; }
Vector2 Flagella::getPositionVector() const { return _positionVector; }

void Flagella::setActivationEnergyCost(const float activationEnergyCost) { _activationEnergyCost = activationEnergyCost; }
float Flagella::getActivationEnergyCost() const { return _activationEnergyCost; }