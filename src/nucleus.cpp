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
	_reproductionNutrientThreshold = 0.5;
	_reproductionEnergyThreshold = 0.5;
}

Nucleus::~Nucleus() {}

void Nucleus::activate(CellState *cellState) {
	if (this->getSprite()->get_frame() == this->getSprite()->get_sprite_frames()->get_frame_count("activate") - 1)
		this->getSprite()->stop();

	// Check that total resources are greater than or equal to the activation threshold and the reproduction cost
	bool nutrientThresholdCondition = cellState->getTotalNutrients() >= _reproductionNutrientThreshold * cellState->getNutrientMaximum() && cellState->getTotalNutrients() >= cellState->getReproductionNutrientCost();
	bool energyThresholdCondition = cellState->getTotalEnergy() >= _reproductionEnergyThreshold * cellState->getEnergyMaximum() && cellState->getTotalEnergy() >= cellState->getReproductionEnergyCost();

	if (nutrientThresholdCondition && energyThresholdCondition) {
		cellState->incrementTotalNutrients(-cellState->getReproductionNutrientCost());
		cellState->incrementTotalEnergy(-cellState->getReproductionEnergyCost());

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
	 * ACTIVATION_THRESHOLD: sets _reproductionNutrientThreshold and _reproductionEnergyThreshold
	 */

	if (modifierName == "ACTIVATION_THRESHOLD") {
		setReproductionNutrientThreshold(modifierValue);
		setReproductionEnergyThreshold(modifierValue);
	}
}

void Nucleus::setReproductionNutrientThreshold(const float reproductionNutrientThreshold) {
	if (reproductionNutrientThreshold > 0 && reproductionNutrientThreshold < 1)
		_reproductionNutrientThreshold = reproductionNutrientThreshold;
}

float Nucleus::getReproductionNutrientThreshold() const { return _reproductionNutrientThreshold; }

void Nucleus::setReproductionEnergyThreshold(const float reproductionEnergyThreshold) {
	if (reproductionEnergyThreshold > 0 && reproductionEnergyThreshold < 1)
		_reproductionEnergyThreshold = reproductionEnergyThreshold;
}

float Nucleus::getReproductionEnergyThreshold() const { return _reproductionEnergyThreshold; }

void Nucleus::_ready() {
	AnimatedSprite2D *sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (sprite)
		this->setSprite(sprite);
}