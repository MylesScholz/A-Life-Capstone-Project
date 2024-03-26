#include "nutrient_zone.hpp"

void NutrientZone::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &NutrientZone::_on_body_entered);
	ClassDB::bind_method(D_METHOD("_on_body_exited", "body"), &NutrientZone::_on_body_exited);

	ClassDB::bind_method(D_METHOD("set_total_nutrients", "total_nutrients"), &NutrientZone::setTotalNutrients);
	ClassDB::bind_method(D_METHOD("get_total_nutrients"), &NutrientZone::getTotalNutrients);
	ClassDB::add_property("NutrientZone", PropertyInfo(Variant::FLOAT, "total_nutrients"), "set_total_nutrients", "get_total_nutrients");

	ClassDB::bind_method(D_METHOD("set_nutrient_maximum", "nutrient_maximum"), &NutrientZone::setNutrientMaximum);
	ClassDB::bind_method(D_METHOD("get_nutrient_maximum"), &NutrientZone::getNutrientMaximum);
	ClassDB::add_property("NutrientZone", PropertyInfo(Variant::FLOAT, "nutrient_maximum"), "set_nutrient_maximum", "get_nutrient_maximum");

	ClassDB::bind_method(D_METHOD("set_feeding_rate", "feeding_rate"), &NutrientZone::setFeedingRate);
	ClassDB::bind_method(D_METHOD("get_feeding_rate"), &NutrientZone::getFeedingRate);
	ClassDB::add_property("NutrientZone", PropertyInfo(Variant::FLOAT, "feeding_rate"), "set_feeding_rate", "get_feeding_rate");

	ClassDB::bind_method(D_METHOD("set_regeneration_rate", "regeneration_rate"), &NutrientZone::setRegenerationRate);
	ClassDB::bind_method(D_METHOD("get_regeneration_rate"), &NutrientZone::getRegenerationRate);
	ClassDB::add_property("NutrientZone", PropertyInfo(Variant::FLOAT, "regeneration_rate"), "set_regeneration_rate", "get_regeneration_rate");
}

NutrientZone::NutrientZone() {
	_feedingCells = Vector<Cell *>();
	_totalNutrients = 1000.0;
	_nutrientMaximum = 1000.0;
	_feedingRate = 0.1;
	_regenerationRate = 1.0;
}
NutrientZone::~NutrientZone() {}

void NutrientZone::_on_body_entered(Node *body) {
	// Check that the body is a Cell
	if (body->get_class() != "Cell")
		return;

	Cell *cell = Object::cast_to<Cell>(body);

	// Check if the Cell is already feeding (should be impossible)
	int index = _feedingCells.find(cell);
	if (index < 0)
		// If not, add the Cell to _feedingCells
		_feedingCells.push_back(cell);
}
void NutrientZone::_on_body_exited(Node *body) {
	// Check that the body is a Cell
	if (body->get_class() != "Cell")
		return;

	Cell *cell = Object::cast_to<Cell>(body);

	// Search for the Cell in _feedingCells
	int index = _feedingCells.find(cell);
	if (index >= 0)
		// If found, remove the Cell from _feedingCells
		_feedingCells.remove_at(index);
}

void NutrientZone::setTotalNutrients(const float totalNutrients) {
	if (totalNutrients > 0)
		_totalNutrients = totalNutrients;
}
void NutrientZone::incrementTotalNutrients(const float nutrients) {
	if (_totalNutrients + nutrients < 0)
		_totalNutrients = 0;
	else if (_totalNutrients + nutrients > _nutrientMaximum)
		_totalNutrients = _nutrientMaximum;
	else
		_totalNutrients += nutrients;
}
float NutrientZone::getTotalNutrients() const { return _totalNutrients; }

void NutrientZone::setNutrientMaximum(const float nutrientMaximum) {
	if (nutrientMaximum >= 0)
		_nutrientMaximum = nutrientMaximum;
}
float NutrientZone::getNutrientMaximum() const { return _nutrientMaximum; }

void NutrientZone::setFeedingRate(const float feedingRate) {
	if (feedingRate > 0)
		_feedingRate = feedingRate;
}
float NutrientZone::getFeedingRate() const { return _feedingRate; }

void NutrientZone::setRegenerationRate(const float regenerationRate) {
	if (regenerationRate > 0)
		_regenerationRate = regenerationRate;
}
float NutrientZone::getRegenerationRate() const { return _regenerationRate; }

void NutrientZone::_ready() {
	this->connect("body_entered", Callable(this, "_on_body_entered"));
	this->connect("body_exited", Callable(this, "_on_body_exited"));
}
void NutrientZone::_process(float delta) {
	// Regenerate nutrients
	incrementTotalNutrients(delta * _regenerationRate);

	// Feed each Cell in this NutrientZone
	for (Cell *cell : _feedingCells) {
		// Calculate the feeding amount for this Cell:
		// The total nutrients in this NutrientZone divided equally among currently feeding Cells and multiplied by delta, the feeding rate, and this Cell's scale
		float feedingAmount = delta * _totalNutrients * _feedingRate * cell->getScale() / _feedingCells.size();

		// Cells may not be able to consume the full feeding amount, so get the actual amount consumed
		float actualFeedingAmount = cell->incrementNutrients(feedingAmount);
		// Decrement this NutrientZone's total nutrients by the amount actually consumed by this Cell
		incrementTotalNutrients(-actualFeedingAmount);
	}
}