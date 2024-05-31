#include "nutrient_zone.hpp"
#include "cell_spawner.hpp"

#include <godot_cpp/classes/spin_box.hpp>

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
	_totalNutrients = 1000.0;
	_nutrientMaximum = 1000.0;
	_feedingRate = 0.1;
	_regenerationRate = 1.0;
	_feedingCells = Vector<Cell *>();
	_deleteOnEmpty = false;
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

void NutrientZone::applyScale(const float scale) {
	if (scale < 0 || scale > 1.0)
		return;

	// Apply the scaling to the collision shape and sprite
	this->get_node<CollisionShape2D>("CollisionShape2D")->apply_scale(Vector2(scale, scale));
	this->get_node<Sprite2D>("Sprite2D")->apply_scale(Vector2(scale, scale));
}

void NutrientZone::setTotalNutrients(const float totalNutrients) {
	if (totalNutrients > 0)
		_totalNutrients = totalNutrients;
}
float NutrientZone::incrementTotalNutrients(const float nutrients) {
	// The amount actually incremented may be less than nutrients because of the bounds
	float actualIncrement = 0;

	if (_totalNutrients + nutrients < 0) {
		actualIncrement = _totalNutrients;
		_totalNutrients = 0;
	} else if (_totalNutrients + nutrients > _nutrientMaximum) {
		actualIncrement = _nutrientMaximum - _totalNutrients;
		_totalNutrients = _nutrientMaximum;
	} else {
		actualIncrement = nutrients;
		_totalNutrients += nutrients;
	}

	// Return the amount actually incremented by
	return actualIncrement;
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
	if (regenerationRate >= 0)
		_regenerationRate = regenerationRate;
}
float NutrientZone::getRegenerationRate() const { return _regenerationRate; }

Sprite2D *NutrientZone::getSprite() { return _sprite; }

void NutrientZone::setDeleteOnEmpty(const bool deleteOnEmpty) { _deleteOnEmpty = deleteOnEmpty; }

bool NutrientZone::getDeleteOnEmpty() const { return _deleteOnEmpty; }

void NutrientZone::_ready() {
	this->connect("body_entered", Callable(this, "_on_body_entered"));
	this->connect("body_exited", Callable(this, "_on_body_exited"));

	_sprite = this->get_node<Sprite2D>("Sprite2D");

	// If spawned with no nutrients, delete the NutrientZone
	if (this->getDeleteOnEmpty() && this->getTotalNutrients() == 0) {
		queue_free();
	}
}
void NutrientZone::_process(float delta) {
	DONT_RUN_IN_EDITOR;

	if (delta != 0) {
		// Regenerate nutrients
		incrementTotalNutrients(delta * _regenerationRate);

		// Feed each Cell in this NutrientZone

		// Feeding coefficient: a value that scales the nutrients fed to Cells based on the current delta, the current nutrient level, and the NutrientZone's scale
		float feedingCoefficient = delta * _totalNutrients / this->get_scale().x;
		for (int i = 0; i < _feedingCells.size(); i++) {
			// Calculate the feeding amount for this Cell:
			// The feeding rate divided by the remaining unfed Cells and scaled by the feeding coefficient and the current Cell's scale
			float feedingAmount = _feedingRate * feedingCoefficient * _feedingCells[i]->getScale() / (_feedingCells.size() - i);

			// Cap the feeding amount at 10% of the current nutrients
			feedingAmount = MIN(feedingAmount, 0.1 * _totalNutrients);

			// Make the feeding amount at least 1 so NutrientZones can run out
			feedingAmount = MAX(feedingAmount, 1);

			// The NutrientZone may not have enough nutrients for the calculated feeding amount,
			// so decrement the total nutrients and get the actual amount decremented (negative return value)
			float actualFeedingAmount = -incrementTotalNutrients(-feedingAmount);

			// Delete the NutrientZone if it is empty and set to delete on empty (Note: will not delete unless trying to feed a Cell, should not be a problem)
			if (this->getDeleteOnEmpty() && this->getTotalNutrients() == 0) {
				queue_free();
			}
			// Feed the current Cell the actual feeding amount
			_feedingCells[i]->incrementNutrients(actualFeedingAmount);
		}
	}
}