#include "flagella.hpp"

using namespace godot;

void Flagella::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_movement_force", "movement_force"), &Flagella::setMovementForce);
	ClassDB::bind_method(D_METHOD("get_movement_force"), &Flagella::getMovementForce);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::VECTOR2, "movement_force"), "set_movement_force", "get_movement_force");
}

Flagella::Flagella() {
	_movementForceVector = 1.0;
	_positionVector = 0.0;
	_activationEnergyCost = 1.0;
}
Flagella::~Flagella() {}

void Flagella::activate(CellState *cellState) {
	if (cellState->getTotalEnergy() >= _activationEnergyCost) { //implement movement energy cost threshold
		// UtilityFunctions::print("Flagella activated: ", cellState->getTotalEnergy(), " >= ", _activationEnergyCost);
	}
	else if (cellState->getPostion() <= _positionVector) { //if true, cell is in bounds
		// UtilityFunctions::print("Flagella activated: ", cellState->getPosition(), " <= ", _positionVector);
	}
}

void Flagella::setMovementForce(const Vector2 movementForce) {
	if (movementForce > 0) {
		_movementForceVector = movementForce;
	}
}

Vector2 Flagella::getMovementForce() const { return _movementForce; }