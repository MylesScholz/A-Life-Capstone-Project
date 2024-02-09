#include "cell_state.hpp"
#include "flagella.hpp"

using namespace godot;

void CellState::_bind_methods() {
}

CellState::CellState() {
	_alive = false;
	_age = 0;
	_lifespan = 0;
	_scale = 1;
}
CellState::~CellState() {
}

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
	if (scale > 0)
		_scale *= scale;
}
float CellState::getScale() const { return _scale; }
