#include "cell_state.hpp"

using namespace godot;

void CellState::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_lifespan", "lifespan"),
			&CellState::setLifespan);
	ClassDB::bind_method(D_METHOD("get_lifespan"), &CellState::getLifespan);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "lifespan"),
			"set_lifespan", "get_lifespan");
}

CellState::CellState() {
	_alive = true;
	_age = 0;
	_lifespan = 1;
	_scale = 1;
	_flagella = Flagella;
}
CellState::~CellState() {}

void CellState::setAlive(const bool alive) { _alive = alive; }
bool CellState::getAlive() const { return _alive; }

void CellState::setAge(const float age) {
	if (age >= 0)
		_age = age;
}
void CellState::incrementAge(const float increment) {
	if (_age + increment > 0)
		_age += increment;
	else
		_age = 0;
}
float CellState::getAge() const { return _age; }

void CellState::setLifespan(const float lifespan) {
	if (lifespan > 0)
		_lifespan = lifespan;
}
float CellState::getLifespan() const { return _lifespan; }

void CellState::setScale(const float scale) { _scale = scale; }
void CellState::applyScale(const float scale) {
	if (scale <= 0)
		_scale *= scale;
}
float CellState::getScale() const { return _scale; }

void CellState::setMovementForce(const Vector2 &force) {
	if (_flagella) {
		_flagella = setMovementForce(force)
	}
}

void CellState::getMovementForce() const {
	return _flagella ? _flagella->getMovementForce() : Vector2():
}

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