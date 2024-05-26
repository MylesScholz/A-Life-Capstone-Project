#include "cell_state.hpp"

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

	ClassDB::bind_method(D_METHOD("set_growth_nutrient_cost", "growth_nutrient_cost"), &CellState::setGrowthNutrientCost);
	ClassDB::bind_method(D_METHOD("get_growth_nutrient_cost"), &CellState::getGrowthNutrientCost);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "growth_nutrient_cost"), "set_growth_nutrient_cost", "get_growth_nutrient_cost");

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

	ClassDB::bind_method(D_METHOD("set_growth_energy_cost", "growth_energy_cost"), &CellState::setGrowthEnergyCost);
	ClassDB::bind_method(D_METHOD("get_growth_energy_cost"), &CellState::getGrowthEnergyCost);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "growth_energy_cost"), "set_growth_energy_cost", "get_growth_energy_cost");

	ClassDB::bind_method(D_METHOD("set_total_energy", "total_energy"), &CellState::setTotalEnergy);
	ClassDB::bind_method(D_METHOD("get_total_energy"), &CellState::getTotalEnergy);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "total_energy"), "set_total_energy", "get_total_energy");

	ClassDB::bind_method(D_METHOD("set_energy_maximum", "energy_maximum"), &CellState::setEnergyMaximum);
	ClassDB::bind_method(D_METHOD("get_energy_maximum"), &CellState::getEnergyMaximum);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "energy_maximum"), "set_energy_maximum", "get_energy_maximum");

	ClassDB::bind_method(D_METHOD("set_growth_rate", "growth_rate"), &CellState::setGrowthRate);
	ClassDB::bind_method(D_METHOD("get_growth_rate"), &CellState::getGrowthRate);
	ClassDB::add_property("CellState", PropertyInfo(Variant::FLOAT, "growth_rate"), "set_growth_rate", "get_growth_rate");

	ClassDB::bind_method(D_METHOD("get_age"), &CellState::getAge);
	ClassDB::bind_method(D_METHOD("get_scale"), &CellState::getScale);
	ClassDB::bind_method(D_METHOD("get_alive"), &CellState::getAlive);
}

CellState::CellState() {
	_alive = true;
	_protectedGenes = 0;
	_age = 0.0;
	_birthTime = 0.0;
	_deathTime = NULL;
	_lifespan = 60.0;
	_scale = 1.0;
	_nutrientEnergyConversionRate = -1.0; // An invalid default value so Mitochondria or Ribosomes only set this once
	_homeostasisNutrientCost = 1.0;
	_reproductionNutrientCost = 50.0;
	_growthNutrientCost = 1000.0;
	_homeostasisEnergyCost = 1.0;
	_reproductionEnergyCost = 50.0;
	_growthEnergyCost = 1000.0;
	_totalNutrients = 100.0;
	_totalEnergy = 100.0;
	_energyMaximum = 100.0;
	_nutrientMaximum = 100.0;
	_growthRate = 1.01;
	_nextMovementVector = Vector2();
	_receptorVectors = Vector<Vector2>();
	_mutationChances = Vector<float>();
	_mutationChances.push_back(0.99);
}
CellState::~CellState() {}

void CellState::setAlive(const bool alive) {
	if (_alive && !alive) // If killing a Cell the first time
		_deathTime = Time::get_singleton()->get_ticks_msec() / 1000.0;
	_alive = alive;
}
bool CellState::getAlive() const { return _alive; }

void CellState::increaseProtectedGenes(const int protect) { _protectedGenes += protect; }

int CellState::getProtectedGenes() { return _protectedGenes; }

void CellState::resetProtectedGenes() { _protectedGenes = 0; }

void CellState::setBirthTime(const int currentMsec) { _birthTime = currentMsec / 1000.0; }
float CellState::getBirthTime() const { return _birthTime; }

void CellState::setAge(const float age) {
	if (age >= 0)
		_age = age;
}
float CellState::getAge() const { return _age; }
void CellState::increaseAge(const float delta) { _age += delta; }

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

void CellState::setNutrientEnergyConversionRate(const float nutrientEnergyConversionRate) {
	if (nutrientEnergyConversionRate >= 0.2 && nutrientEnergyConversionRate <= 5)
		_nutrientEnergyConversionRate = nutrientEnergyConversionRate;
}
float CellState::getNutrientEnergyConversionRate() const { return _nutrientEnergyConversionRate; }

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

void CellState::setGrowthNutrientCost(const float growthNutrientCost) {
	if (growthNutrientCost >= 0)
		_growthNutrientCost = growthNutrientCost;
}
float CellState::getGrowthNutrientCost() const { return _growthNutrientCost; }

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
	if (nutrientMaximum >= 0) {
		_nutrientMaximum = nutrientMaximum;
		if (_totalNutrients > _nutrientMaximum)
			_totalNutrients = _nutrientMaximum;
	}
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

void CellState::setGrowthEnergyCost(const float growthEnergyCost) {
	if (growthEnergyCost >= 0)
		_growthEnergyCost = growthEnergyCost;
}
float CellState::getGrowthEnergyCost() const { return _growthEnergyCost; }

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
	if (energyMaximum >= 0) {
		_energyMaximum = energyMaximum;
		if (_totalEnergy > _energyMaximum)
			_totalEnergy = _energyMaximum;
	}
}
float CellState::getEnergyMaximum() const { return _energyMaximum; }

void CellState::setGrowthRate(const float growthRate) {
	if (growthRate > 1)
		_growthRate = growthRate;
}
float CellState::getGrowthRate() const { return _growthRate; }

void CellState::setNextMovementVector(const Vector2 nextMovementVector) { _nextMovementVector = nextMovementVector; }
Vector2 CellState::getNextMovementVector() const { return _nextMovementVector; }

void CellState::setReceptorVectors(const Vector<Vector2> receptorVectors) { _receptorVectors = receptorVectors; }
Vector<Vector2> CellState::getReceptorVectors() const { return _receptorVectors; }

void CellState::addMutationChance(const float chance) {
	_mutationChances.push_back(chance);
}

float CellState::getMutationChance(const int index) {
	return _mutationChances[index];
}

int CellState::getMutationChanceCount() const {
	return _mutationChances.size();
}

void CellState::_ready() {
	_birthTime = Time::get_singleton()->get_ticks_msec() / 1000.0;
}
