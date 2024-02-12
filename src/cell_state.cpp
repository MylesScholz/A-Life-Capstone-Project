#include "cell_state.hpp"

using namespace godot;

void CellState::_bind_methods() {}

CellState::CellState() {
	_alive = true;
	_birthTime = Time::get_singleton()->get_ticks_msec() / 1000.0;
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

void CellState::setBirthTime(const int currentMsec) { _birthTime = currentMsec / 1000.; }
float CellState::getBirthTime() const { return _birthTime; }
float CellState::getAge(const int currentMsec) const { return (currentMsec / 1000.) - _birthTime; }

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
