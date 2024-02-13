#include "nucleus.hpp"

using namespace godot;

void Nucleus::_bind_methods() {
	//Reproduction Threshold Variable
	ClassDB::bind_method(D_METHOD("set_reproductionNutrientThreshold", "reproductionNutrientThreshold"), &Nucleus::setReproductionNutrientThreshold);
	ClassDB::bind_method(D_METHOD("get_reproductionNutrientThreshold"), &Nucleus::getReproductionNutrientThreshold);
	ClassDB::add_property("Nucleus", PropertyInfo(Variant::FLOAT, "Reproduction Nutrient Threshold"), "set_reproductionNutrientThreshold", "get_reproductionNutrientThreshold");
}

Nucleus::Nucleus() {
	_reproductionNutrientThreshold = 2.0;
}

Nucleus::~Nucleus() {}

void Nucleus::setReproductionNutrientThreshold(const float reproductionNutrientThreshold) {
	if (reproductionNutrientThreshold > 0) {
		_reproductionNutrientThreshold = reproductionNutrientThreshold;
	}
}

float Nucleus::getReproductionNutrientThreshold() const { return _reproductionNutrientThreshold; }