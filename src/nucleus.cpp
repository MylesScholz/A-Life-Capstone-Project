#include "nucleus.hpp"
#include "cell.hpp"


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
	// This should be somewhere else, or maybe should be a multiplier to the reproduction nutrient cost?
	constexpr float baseCost = 5.0;
	
	if (cellState->getTotalNutrients() >= _reproductionNutrientThreshold && cellState->getTotalEnergy() >= _reproductionEnergyThreshold) {

		cellState->incrementTotalNutrients(-cellState->getReproductionNutrientCost() - baseCost);
		cellState->incrementTotalEnergy(-cellState->getReproductionEnergyCost() - baseCost);

		cellState->setTotalNutrients(cellState->getTotalNutrients() / 2);
		cellState->setTotalEnergy(cellState->getTotalEnergy() / 2);

		// I think this may sometimes be segfaulting? not totally sure
		Cell* cell = Object::cast_to<Cell>(cellState->get_parent());

		this->emit_signal("cell_reproduction", cell);
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

void Nucleus::setReproductionEnergyThreshold(const float reproductionEnergyThreshold){
	if (reproductionEnergyThreshold > 0) {
		_reproductionEnergyThreshold = reproductionEnergyThreshold;
	}
}

float Nucleus::getReproductionEnergyThreshold() const { return _reproductionEnergyThreshold; }

void Nucleus::_ready() {
	AnimatedSprite2D *sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (sprite)
		this->setSprite(sprite);
}