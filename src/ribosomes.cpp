#include "ribosomes.hpp"

void Ribosomes::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_activation_threshold", "activation_threshold"), &Ribosomes::setActivationThreshold);
	ClassDB::bind_method(D_METHOD("get_activation_threshold"), &Ribosomes::getActivationThreshold);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::FLOAT, "activation_threshold"), "set_activation_threshold", "get_activation_threshold");

	ClassDB::bind_method(D_METHOD("set_strength", "strength"), &Ribosomes::setStrength);
	ClassDB::bind_method(D_METHOD("get_strength"), &Ribosomes::getStrength);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::FLOAT, "strength"), "set_strength", "get_strength");

	ClassDB::bind_method(D_METHOD("set_efficiency", "efficiency"), &Ribosomes::setEfficiency);
	ClassDB::bind_method(D_METHOD("get_efficiency"), &Ribosomes::getEfficiency);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::FLOAT, "efficiency"), "set_efficiency", "get_efficiency");

	ClassDB::bind_method(D_METHOD("set_conversion_rate", "conversion_rate"), &Ribosomes::setConversionRate);
	ClassDB::bind_method(D_METHOD("get_conversion_rate"), &Ribosomes::getConversionRate);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::FLOAT, "conversion_rate"), "set_conversion_rate", "get_conversion_rate");

	ClassDB::bind_method(D_METHOD("set_activation_resource", "activation_resource"), &Ribosomes::setActivationResource);
	ClassDB::bind_method(D_METHOD("get_activation_resource"), &Ribosomes::getActivationResource);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::STRING, "activation_resource"), "set_activation_resource", "get_activation_resource");

	ClassDB::bind_method(D_METHOD("set_threshold_type", "threshold_type"), &Ribosomes::setThresholdType);
	ClassDB::bind_method(D_METHOD("get_threshold_type"), &Ribosomes::getThresholdType);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::STRING, "threshold_type"), "set_threshold_type", "get_threshold_type");
}

Ribosomes::Ribosomes() {
	// CellStructure attributes
	this->setCreationNutrientCost(10.0);
	this->setMaintenanceNutrientCost(1.0);
	this->setCreationEnergyCost(10.0);
	this->setMaintenanceEnergyCost(1.0);

	// Ribosomes attributes
	_activationThreshold = 1.0;
	_strength = 1.0;
	_efficiency = 1.0;
	_conversionRate = 1.0;
	_activationResource = "energy";
	_thresholdType = "high-pass";
}
Ribosomes::~Ribosomes() {}

void Ribosomes::activate(CellState *cellState) {
	bool thresholdCondition = false;

	// Check whether these Ribosomes listen to "nutrients" or "energy" to determine activation
	if (_activationResource == "nutrients") {
		// Set thresholdCondition by whether the proportion of total nutrients in the cellState meet a high-pass or low-pass threshold
		if (_thresholdType == "high-pass") {
			thresholdCondition = cellState->getTotalNutrients() / cellState->getNutrientMaximum() >= _activationThreshold;
		} else if (_thresholdType == "low-pass") {
			thresholdCondition = cellState->getTotalNutrients() / cellState->getNutrientMaximum() <= _activationThreshold;
		}
	} else if (_activationResource == "energy") {
		// Set thresholdCondition by whether the proportion of total energy in the cellState meets a high-pass or low-pass threshold
		if (_thresholdType == "high-pass") {
			thresholdCondition = cellState->getTotalEnergy() / cellState->getEnergyMaximum() >= _activationThreshold;
		} else if (_thresholdType == "low-pass") {
			thresholdCondition = cellState->getTotalEnergy() / cellState->getEnergyMaximum() <= _activationThreshold;
		}
	}

	// Check whether the threshold is met
	if (thresholdCondition) {
		// UtilityFunctions::print("Ribosomes activated");

		// Decrement the energy based on the strength and efficiency of these Ribosomes
		cellState->incrementTotalEnergy(-_efficiency * _strength);
		// Increment the nutrients based on the strength, conversion rate (nutrients:energy), and efficiency of these Ribosomes
		cellState->incrementTotalNutrients(_efficiency * _conversionRate * _strength);
	}
}

void Ribosomes::setActivationThreshold(const float activationThreshold) {
	if (activationThreshold >= 0.0 && activationThreshold <= 1.0)
		_activationThreshold = activationThreshold;
}
float Ribosomes::getActivationThreshold() const { return _activationThreshold; }

void Ribosomes::setStrength(const float strength) {
	if (strength > 0.0)
		_strength = strength;
}
float Ribosomes::getStrength() const { return _strength; }

void Ribosomes::setEfficiency(const float efficiency) {
	if (efficiency >= 0.0 && efficiency <= 1.0)
		_efficiency = efficiency;
}
float Ribosomes::getEfficiency() const { return _efficiency; }

void Ribosomes::setConversionRate(const float conversionRate) {
	if (conversionRate > 0.0)
		_conversionRate = conversionRate;
}
float Ribosomes::getConversionRate() const { return _conversionRate; }

void Ribosomes::setActivationResource(const String activationResource) {
	if (activationResource == "nutrients" || activationResource == "energy")
		_activationResource = activationResource;
}
String Ribosomes::getActivationResource() const { return _activationResource; }

void Ribosomes::setThresholdType(const String thresholdType) {
	if (thresholdType == "high-pass" || thresholdType == "low-pass")
		_thresholdType = thresholdType;
}
String Ribosomes::getThresholdType() const { return _thresholdType; }

void Ribosomes::_ready() {
	Sprite2D *sprite = this->get_node<Sprite2D>("Sprite2D");
	if (sprite)
		this->setSprite(sprite);
}
