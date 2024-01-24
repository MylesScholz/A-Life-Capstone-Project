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
	_nutrients = 26;
	_nutrient_maximum = 26;
	_nutrient_efficiency = 1;
	_homeostasis_level = 5;
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

void CellState::addNutrients(float nutrients) {
	nutrients *= _nutrient_efficiency;
	if (_nutrients + nutrients > _nutrient_maximum)
		nutrients = _nutrient_maximum;
	else
		_nutrients += nutrients;
}

void CellState::decrementNutrients(const float decrement) {
	if (_nutrients - decrement > 0)
		_nutrients -= decrement;
	else if (_nutrients - decrement <= 0)
		_nutrients = 0;
}

float CellState::getNutrients() const { return _nutrients; }