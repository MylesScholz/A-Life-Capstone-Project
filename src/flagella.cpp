#include "flagella.hpp"

using namespace godot;

void Flagella::_bind_methods() {}

Flagella::Flagella() {
	_movementForce = Vector2();
}
Flagella::~Flagella() {}

void Flagella::setMovementForce(const Vector2 &movementForce) {
	_movementForce = movementForce;
}

Vector2 Flagella::getMovementForce() const { return _movementForce; }