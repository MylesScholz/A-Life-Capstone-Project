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
	// Flagella attributes
	_movementForceVector = Vector2(0, 1);
	_positionVector = Vector2();
	_activationEnergyCost = 1.0;
	_activationEnergyThreshold = 1.0;

	rand.instantiate();
}
Flagella::~Flagella() {}

void Flagella::activate(CellState *cellState) {
	if (this->getSprite()->get_frame() == this->getSprite()->get_sprite_frames()->get_frame_count("activate") - 1)
		this->getSprite()->stop();

	bool thresholdCondition = false;

	if (cellState->getTotalEnergy() >= _activationEnergyCost) {
		thresholdCondition = cellState->getTotalEnergy() / cellState->getEnergyMaximum() >= _activationEnergyThreshold;
	}

	if (thresholdCondition) {
		// Sum the activated receptor vectors to get the direction towards a NutrientZone
		Vector2 force = Vector2();
		for (Vector2 receptorVector : cellState->getReceptorVectors())
			force += receptorVector.normalized();
		// Scale the force by the movement force vector magnitude and the size of the Cell
		force *= _movementForceVector.length() * cellState->getScale();

		// If there are no activated Receptors, move in a random direction
		if (cellState->getReceptorVectors().size() == 0) {
			float direction = rand->randf_range(0, 2 * Math_PI);
			force = _movementForceVector.rotated(direction) * cellState->getScale();
		}

		// Set the next movement vector
		cellState->setNextMovementVector(force);
		// Subtract the energy cost of activating the Flagella, scaled by the magnitude of the force
		cellState->incrementTotalEnergy(-(_activationEnergyCost * force.length()));

		this->getSprite()->set_frame(rand->randi_range(1, 2));
		this->getSprite()->play("activate");
	} else {
		cellState->setNextMovementVector(Vector2(0, 0));
	}
}

void Flagella::modify(String modifierName, float modifierValue) {
	/*
	 * Relevant ModifierGenes
	 * ACTIVATION_THRESHOLD: sets _activationEnergyThreshold
	 * STRENGTH: multiplies _movementForceVector
	 * N_SUBSTRUCTURES: (not yet implemented)
	 */

	if (modifierName == "ACTIVATION_THRESHOLD") {
		setActivationEnergyThreshold(modifierValue);
	} else if (modifierName == "STRENGTH") {
		setMovementForceVector(getMovementForceVector() * modifierValue);
	} else if (modifierName == "N_SUBSTRUCTURES") {
		// Set the number of Flagella
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
	AnimatedSprite2D *sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (sprite)
		this->setSprite(sprite);
}