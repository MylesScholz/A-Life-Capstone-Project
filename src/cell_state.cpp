#include "cell_state.hpp"

using namespace godot;

void CellState::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_lifespan", "lifespan"), &CellState::setLifespan);
	ClassDB::bind_method(D_METHOD("get_lifespan"), &CellState::getLifespan);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "lifespan"), "set_lifespan", "get_lifespan");

	ClassDB::bind_method(D_METHOD("set_homeostasis_nutrient_cost", "homeostasis_nutrient_cost"), &CellState::setHomeostasisNutrientCost);
	ClassDB::bind_method(D_METHOD("get_homeostasis_nutrient_cost"), &CellState::getHomeostasisNutrientCost);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "homeostasis_nutrient_cost"), "set_homeostasis_nutrient_cost", "get_homeostasis_nutrient_cost");

	ClassDB::bind_method(D_METHOD("set_reproduction_nutrient_cost", "reproduction_nutrient_cost"), &CellState::setReproductionNutrientCost);
	ClassDB::bind_method(D_METHOD("get_reproduction_nutrient_cost"), &CellState::getReproductionNutrientCost);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "reproduction_nutrient_cost"), "set_reproduction_nutrient_cost", "get_reproduction_nutrient_cost");

	ClassDB::bind_method(D_METHOD("set_total_nutrients", "total_nutrients"), &CellState::setTotalNutrients);
	ClassDB::bind_method(D_METHOD("get_total_nutrients"), &CellState::getTotalNutrients);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "total_nutrients"), "set_total_nutrients", "get_total_nutrients");

	ClassDB::bind_method(D_METHOD("set_nutrient_maximum", "nutrient_maximum"), &CellState::setNutrientMaximum);
	ClassDB::bind_method(D_METHOD("get_nutrient_maximum"), &CellState::getNutrientMaximum);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "nutrient_maximum"), "set_nutrient_maximum", "get_nutrient_maximum");

	ClassDB::bind_method(D_METHOD("set_homeostasis_energy_cost", "homeostasis_energy_cost"), &CellState::setHomeostasisEnergyCost);
	ClassDB::bind_method(D_METHOD("get_homeostasis_energy_cost"), &CellState::getHomeostasisEnergyCost);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "homeostasis_energy_cost"), "set_homeostasis_energy_cost", "get_homeostasis_energy_cost");

	ClassDB::bind_method(D_METHOD("set_reproduction_energy_cost", "reproduction_energy_cost"), &CellState::setReproductionEnergyCost);
	ClassDB::bind_method(D_METHOD("get_reproduction_energy_cost"), &CellState::getReproductionEnergyCost);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "reproduction_energy_cost"), "set_reproduction_energy_cost", "get_reproduction_energy_cost");

	ClassDB::bind_method(D_METHOD("set_total_energy", "total_energy"), &CellState::setTotalEnergy);
	ClassDB::bind_method(D_METHOD("get_total_energy"), &CellState::getTotalEnergy);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "total_energy"), "set_total_energy", "get_total_energy");

	ClassDB::bind_method(D_METHOD("set_energy_maximum", "energy_maximum"), &CellState::getEnergyMaximum);
	ClassDB::bind_method(D_METHOD("get_energy_maximum"), &CellState::setEnergyMaximum);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "energy_maximum"), "set_energy_maximum", "get_energy_maximum");
}

CellState::CellState() {
	_alive = true;
	_birthTime = 0.0;
	_lifespan = 60.0;
	_scale = 1.0;
	_homeostasisNutrientCost = 1.0;
	_reproductionNutrientCost = 50.0;
	_homeostasisEnergyCost = 1.0;
	_reproductionEnergyCost = 50.0;
	_totalNutrients = 100.0;
	_totalEnergy = 100.0;
	_energyMaximum = 100.0;
	_nutrientMaximum = 100.0;
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

void CellState::setHomeostasisEnergyCost(const float homeostasisEnergyCost) {
	if (homeostasisEnergyCost > 0)
		_homeostasisEnergyCost = homeostasisEnergyCost;
}
float CellState::getHomeostasisEnergyCost() const { return _homeostasisEnergyCost; }

void CellState::setReproductionEnergyCost(const float reproductionEnergyCost) {
	if (reproductionEnergyCost > 0)
		_reproductionEnergyCost = reproductionEnergyCost;
}
float CellState::getReproductionEnergyCost() const { return _reproductionEnergyCost; }

void CellState::setTotalEnergy(const float totalEnergy) {
	if (totalEnergy < 0)
		_totalEnergy = 0;
	else if (totalEnergy > _energyMaximum)
		_totalEnergy = _energyMaximum;
	else
		_totalEnergy = totalEnergy;
}
void CellState::incrementTotalEnergy(const float energy) {
	if (_totalEnergy + energy < 0)
		_totalEnergy = 0;
	else if (_totalEnergy + energy > _energyMaximum)
		_totalEnergy = _energyMaximum;
	else
		_totalEnergy += energy;
}
float CellState::getTotalEnergy() const { return _totalEnergy; }

void CellState::setEnergyMaximum(const float energyMaximum) {
	if (energyMaximum >= 0)
		_energyMaximum = energyMaximum;
}
float CellState::getEnergyMaximum() const { return _energyMaximum; }

void CellState::setNextMovementVector(const Vector2 nextMovementVector) {
	_nextMovementVector = nextMovementVector;
}
Vector2 CellState::getNextMovementVector() const { return _nextMovementVector; }

void CellState::_ready() {
	_birthTime = Time::get_singleton()->get_ticks_msec() / 1000.0;
}
