#include "flagella.hpp"

using namespace godot;

void Flagella::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_movement_force", "movement_force"), &Flagella::setMovementForceVector);
	ClassDB::bind_method(D_METHOD("get_movement_force"), &Flagella::getMovementForceVector);
	ClassDB::add_property("Flagella", PropertyInfo(Variant::VECTOR2, "movement_force"), "set_movement_force", "get_movement_force");
}

Flagella::Flagella() {
	_movementForceVector = Vector2();
	_positionVector = Vector2();
	_activationEnergyCost = 1.0;
}
Flagella::~Flagella() {}

void Flagella::activate(CellState *cellState) {
	if (cellState->getTotalEnergy() >= _activationEnergyCost) { //implement movement energy cost threshold
		// UtilityFunctions::print("Flagella activated: ", cellState->getTotalEnergy(), " >= ", _activationEnergyCost);
	}
}

void Flagella::setMovementForceVector(const Vector2 movementForceVector) { _movementForceVector = movementForceVector; }
Vector2 Flagella::getMovementForceVector() const { return _movementForceVector; }