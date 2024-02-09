#include "flagella.hpp"

using namespace godot;

void Flagella::_bind_methods() {
}

Flagella::Flagella() {
	_movement_force = Vector2();
}
Flagella::~Flagella() {}

void Flagella::setMovementForce(const Vector2 &force) {
	_movement_force = force;
}

Vector2 Flagella::getMovementForce() const {
	return _movement_force;
}