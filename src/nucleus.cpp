#include "nucleus.hpp"

void Nucleus::_bind_methods() {
	//Reproduction Threshold Variable
	ClassDB::bind_method(D_METHOD("set_reproduction_nutrient_threshold", "reproduction_nutrient_threshold"), &Nucleus::setReproductionNutrientThreshold);
	ClassDB::bind_method(D_METHOD("get_reproduction_nutrient_threshold"), &Nucleus::getReproductionNutrientThreshold);
	ClassDB::add_property("Nucleus", PropertyInfo(Variant::FLOAT, "reproduction_nutrient_threshold"), "set_reproduction_nutrient_threshold", "get_reproduction_nutrient_threshold");
}

Nucleus::Nucleus() {
	_reproductionNutrientThreshold = 2.0;
}

Nucleus::~Nucleus() {}

void Nucleus::activate(CellState *cellState) {
	if (this->getSprite()->get_frame() == this->getSprite()->get_sprite_frames()->get_frame_count("activate") - 1)
		this->getSprite()->stop();

	if (cellState->getTotalNutrients() >= _reproductionNutrientThreshold) {
		// UtilityFunctions::print("Nucleus activated: ", cellState->getTotalNutrients(), " >= ", _reproductionNutrientThreshold);

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