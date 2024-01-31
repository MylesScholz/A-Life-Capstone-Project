#include "mitochondria.hpp"

using namespace godot;

void Mitochondria::_bind_methods() {
	ClassDB::bind_method(D_METHOD("add_nutrients", "amount"), &Mitochondria::addNutrients);
	ClassDB::bind_method(D_METHOD("decrement_nutrients", "amount"), &Mitochondria::decrementNutrients);
	ClassDB::bind_method(D_METHOD("get_nutrients"), &Mitochondria::getNutrients);
	ClassDB::bind_method(D_METHOD("set_nutrients", "level"), &Mitochondria::setNutrients);
	ClassDB::add_property("Mitochondria", PropertyInfo(Variant::FLOAT, "nutrients"),
			"set_nutrients", "get_nutrients");
}

Mitochondria::Mitochondria() {
	_nutrients = 26;
	_nutrient_maximum = 26;
	_nutrient_efficiency = 1;
}
Mitochondria::~Mitochondria() {}

void Mitochondria::addNutrients(float nutrients) {
	nutrients *= _nutrient_efficiency;
	if (_nutrients + nutrients > _nutrient_maximum)
		nutrients = _nutrient_maximum;
	else
		_nutrients += nutrients;
}

void Mitochondria::decrementNutrients(const float decrement) {
	if (_nutrients - decrement > 0)
		_nutrients -= decrement;
	else if (_nutrients - decrement <= 0)
		_nutrients = 0;
}

float Mitochondria::getNutrients() const { return _nutrients; }

void Mitochondria::setNutrients(const float level) {
	_nutrients = level;
}