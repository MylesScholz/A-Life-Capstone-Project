#include "flagella.hpp"

using namespace godot;

void Flagella:_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_movement_force", "force"),
			&Flagella::setMovementForce);
	ClassDB::bind_method(D_METHOD("get_movement_force", &Flagella:getMovementForce));
	ClassDB::add_property("Flagella", PropertyInfo(Variant::VECTOR2, "movement_force"),
			"set_movement_force", "get_lifespan");
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