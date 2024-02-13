#include "cell_state.hpp"

using namespace godot;

void CellState::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_lifespan", "lifespan"), &CellState::setLifespan);
	ClassDB::bind_method(D_METHOD("get_lifespan"), &CellState::getLifespan);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "lifespan"), "set_lifespan", "get_lifespan");

	ClassDB::bind_method(D_METHOD("set_homeostasisNutrientCost", "homeostasisNutrientCost"), &CellState::setHomeostasisNutrientCost);
	ClassDB::bind_method(D_METHOD("get_homeostasisNutrientCost"), &CellState::getHomeostasisNutrientCost);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "homeostasis_nutrient_cost"), "set_homeostasisNutrientCost", "get_homeostasisNutrientCost");

	ClassDB::bind_method(D_METHOD("set_reproductionNutrientCost", "reproductionNutrientCost"), &CellState::setReproductionNutrientCost);
	ClassDB::bind_method(D_METHOD("get_reproductionNutrientCost"), &CellState::getReproductionNutrientCost);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "reproduction_nutrient_cost"), "set_reproductionNutrientCost", "get_reproductionNutrientCost");

	ClassDB::bind_method(D_METHOD("set_totalNutrients", "totalNutrients"), &CellState::setTotalNutrients);
	ClassDB::bind_method(D_METHOD("get_totalNutrients"), &CellState::getTotalNutrients);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "total_nutrients"), "set_totalNutrients", "get_totalNutrients");

	ClassDB::bind_method(D_METHOD("set_nutrientMaximum", "nutrientMaximum"), &CellState::setNutrientMaximum);
	ClassDB::bind_method(D_METHOD("get_nutrientMaximum"), &CellState::getNutrientMaximum);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "nutrient_maximum"), "set_nutrientMaximum", "get_nutrientMaximum");
}

CellState::CellState() {
	_alive = true;
	_birthTime = 0.0;
	_lifespan = 1.0;
	_scale = 1.0;
	_homeostasisNutrientCost = 1.0;
	_reproductionNutrientCost = 1.0;
	_totalNutrients = 0.0;
	_nutrientMaximum = 1.0;
}
CellState::~CellState() {}

void CellState::setAlive(const bool alive) { _alive = alive; }
bool CellState::getAlive() const { return _alive; }

void CellState::setBirthTime(const int currentMsec) { _birthTime = currentMsec / 1000.0; }
float CellState::getBirthTime() const { return _birthTime; }
float CellState::getAge(const int currentMsec) const { return (currentMsec / 1000.0) - _birthTime; }

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

void CellState::setHomeostasisNutrientCost(const float homeostasisNutrientCost) {
	if (homeostasisNutrientCost > 0)
		_homeostasisNutrientCost = homeostasisNutrientCost;
}
float CellState::getHomeostasisNutrientCost() const { return _homeostasisNutrientCost; }

void CellState::setReproductionNutrientCost(const float reproductionNutrientCost) {
	if (reproductionNutrientCost > 0)
		_reproductionNutrientCost = reproductionNutrientCost;
}
float CellState::getReproductionNutrientCost() const { return _reproductionNutrientCost; }

void CellState::setTotalNutrients(const float totalNutrients) {
	if (totalNutrients < 0)
		_totalNutrients = 0;
	else if (totalNutrients > _nutrientMaximum)
		_totalNutrients = _nutrientMaximum;
	else
		_totalNutrients = totalNutrients;
}
void CellState::incrementTotalNutrients(const float nutrients) {
	if (_totalNutrients + nutrients < 0)
		_totalNutrients = 0;
	else if (_totalNutrients + nutrients > _nutrientMaximum)
		_totalNutrients = _nutrientMaximum;
	else
		_totalNutrients += nutrients;
}
float CellState::getTotalNutrients() const { return _totalNutrients; }

void CellState::setNutrientMaximum(const float nutrientMaximum) {
	if (nutrientMaximum >= 0)
		_nutrientMaximum = nutrientMaximum;
}
float CellState::getNutrientMaximum() const { return _nutrientMaximum; }

void CellState::_ready() {
	_birthTime = Time::get_singleton()->get_ticks_msec() / 1000.0;
}
