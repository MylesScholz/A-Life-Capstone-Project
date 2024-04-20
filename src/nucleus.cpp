#include "nucleus.hpp"
#include "cell.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

void Nucleus::_bind_methods() {
	//Reproduction Threshold Variable
	ClassDB::bind_method(D_METHOD("set_reproduction_nutrient_threshold", "reproduction_nutrient_threshold"), &Nucleus::setReproductionNutrientThreshold);
	ClassDB::bind_method(D_METHOD("get_reproduction_nutrient_threshold"), &Nucleus::getReproductionNutrientThreshold);
	ClassDB::add_property("Nucleus", PropertyInfo(Variant::FLOAT, "reproduction_nutrient_threshold"), "set_reproduction_nutrient_threshold", "get_reproduction_nutrient_threshold");

	ADD_SIGNAL(MethodInfo("cell_reproduction", PropertyInfo(Variant::OBJECT, "cell")));
}

Nucleus::Nucleus() {
	_reproductionNutrientThreshold = 50.0;
	_reproductionEnergyThreshold = 50.0;
}

Nucleus::~Nucleus() {}

void Nucleus::activate(CellState *cellState) {
	if (this->getSprite()->get_frame() == this->getSprite()->get_sprite_frames()->get_frame_count("activate") - 1)
		this->getSprite()->stop();

	// This should be somewhere else, or maybe should be a multiplier to the reproduction nutrient cost?
	float baseCost = 5.0;

	// Need to figure out avoiding reproduction when cells are immortal
	if (cellState->getTotalNutrients() >= _reproductionNutrientThreshold && cellState->getTotalEnergy() >= _reproductionEnergyThreshold) {
		UtilityFunctions::print("About to reproduce. Current nutrients: ", cellState->getTotalNutrients());

		cellState->incrementTotalNutrients(-cellState->getReproductionNutrientCost() - baseCost);
		cellState->incrementTotalEnergy(-cellState->getReproductionEnergyCost() - baseCost);

		cellState->setTotalNutrients(cellState->getTotalNutrients() / 2);
		cellState->setTotalEnergy(cellState->getTotalEnergy() / 2);

		Cell *cell = Object::cast_to<Cell>(cellState->get_parent());

		this->emit_signal("cell_reproduction", cell);

		this->getSprite()->set_frame(1);
		this->getSprite()->play("activate");
	}
}

void Nucleus::modify(String modifierName, float modifierValue) {
	/*
	 * Relevant ModifierGenes
	 * ACTIVATION_THRESHOLD: sets _reproductionNutrientThreshold
	 */

	if (modifierName == "ACTIVATION_THRESHOLD") {
		setReproductionNutrientThreshold(modifierValue);
	}
}

void Nucleus::setReproductionNutrientThreshold(const float reproductionNutrientThreshold) {
	if (reproductionNutrientThreshold > 0) {
		_reproductionNutrientThreshold = reproductionNutrientThreshold;
	}
}

float Nucleus::getReproductionNutrientThreshold() const { return _reproductionNutrientThreshold; }

void Nucleus::_ready() {
	AnimatedSprite2D *sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (sprite)
		this->setSprite(sprite);
}