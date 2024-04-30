#include "mitochondria.hpp"

void Mitochondria::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_activation_threshold", "activation_threshold"), &Mitochondria::setActivationThreshold);
	ClassDB::bind_method(D_METHOD("get_activation_threshold"), &Mitochondria::getActivationThreshold);
	ClassDB::add_property("Mitochondria", PropertyInfo(Variant::FLOAT, "activation_threshold"), "set_activation_threshold", "get_activation_threshold");

	ClassDB::bind_method(D_METHOD("set_strength", "strength"), &Mitochondria::setStrength);
	ClassDB::bind_method(D_METHOD("get_strength"), &Mitochondria::getStrength);
	ClassDB::add_property("Mitochondria", PropertyInfo(Variant::FLOAT, "strength"), "set_strength", "get_strength");

	ClassDB::bind_method(D_METHOD("set_efficiency", "efficiency"), &Mitochondria::setEfficiency);
	ClassDB::bind_method(D_METHOD("get_efficiency"), &Mitochondria::getEfficiency);
	ClassDB::add_property("Mitochondria", PropertyInfo(Variant::FLOAT, "efficiency"), "set_efficiency", "get_efficiency");

	ClassDB::bind_method(D_METHOD("set_conversion_rate", "conversion_rate"), &Mitochondria::setConversionRate);
	ClassDB::bind_method(D_METHOD("get_conversion_rate"), &Mitochondria::getConversionRate);
	ClassDB::add_property("Mitochondria", PropertyInfo(Variant::FLOAT, "conversion_rate"), "set_conversion_rate", "get_conversion_rate");

	ClassDB::bind_method(D_METHOD("set_activation_resource", "activation_resource"), &Mitochondria::setActivationResource);
	ClassDB::bind_method(D_METHOD("get_activation_resource"), &Mitochondria::getActivationResource);
	ClassDB::add_property("Mitochondria", PropertyInfo(Variant::STRING, "activation_resource"), "set_activation_resource", "get_activation_resource");

	ClassDB::bind_method(D_METHOD("set_threshold_type", "threshold_type"), &Mitochondria::setThresholdType);
	ClassDB::bind_method(D_METHOD("get_threshold_type"), &Mitochondria::getThresholdType);
	ClassDB::add_property("Mitochondria", PropertyInfo(Variant::STRING, "threshold_type"), "set_threshold_type", "get_threshold_type");
}

Mitochondria::Mitochondria() {
	// Mitochondria attributes
	_activationThreshold = 0.5;
	_strength = 1.0;
	_efficiency = 1.0;
	_conversionRate = 1.0;
	_activationResource = "energy";
	_thresholdType = "low-pass";
}
Mitochondria::~Mitochondria() {}

void Mitochondria::activate(CellState *cellState) {
	if (this->getSprite()->get_frame() == this->getSprite()->get_sprite_frames()->get_frame_count("activate") - 1)
		this->getSprite()->stop();

	bool thresholdCondition = false;

	// Check whether these Mitochondria listen to "nutrients" or "energy" to determine activation
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
		// UtilityFunctions::print("Mitochondria activated");

		// Decrement the nutrients based on the strength and efficiency of these Mitochondria
		cellState->incrementTotalNutrients(-_efficiency * _strength);
		// Increment the energy based on the strength, conversion rate (energy:nutrients), and efficiency of these Mitochondria
		cellState->incrementTotalEnergy(_efficiency * _conversionRate * _strength);

		this->getSprite()->set_frame(1);
		this->getSprite()->play("activate");
	}
}

void Mitochondria::modify(String modifierName, float modifierValue) {
	/*
	 * Relevant ModifierGenes
	 * ACTIVATION_THRESHOLD: sets _activationThreshold
	 * STRENGTH: sets _strength
	 * CONVERSION_RATE: sets _conversionRate
	 * ACTIVATION_RESOURCE: sets _activationResource (0 -> "nutrients", 1 -> "energy")
	 * THRESHOLD_TYPE: sets _thresholdType (0 -> "low-pass", 1 -> "high-pass")
	 */

	if (modifierName == "ACTIVATION_THRESHOLD") {
		setActivationThreshold(modifierValue);
	} else if (modifierName == "STRENGTH") {
		setStrength(modifierValue);
	} else if (modifierName == "CONVERSION_RATE") {
		setConversionRate(modifierValue);
	} else if (modifierName == "ACTIVATION_RESOURCE") {
		// Map float modifierValue to String _activationResource
		if (modifierValue == 0) {
			setActivationResource("nutrients");
		} else if (modifierValue == 1) {
			setActivationResource("energy");
		}
	} else if (modifierName == "THRESHOLD_TYPE") {
		// Map float modifierValue to String _thresholdType
		if (modifierValue == 0) {
			setThresholdType("low-pass");
		} else if (modifierValue == 1) {
			setThresholdType("high-pass");
		}
	}
}

void Mitochondria::setActivationThreshold(const float activationThreshold) {
	if (activationThreshold >= 0.0 && activationThreshold <= 1.0)
		_activationThreshold = activationThreshold;
}
float Mitochondria::getActivationThreshold() const { return _activationThreshold; }

void Mitochondria::setStrength(const float strength) {
	if (strength > 0.0)
		_strength = strength;
}
float Mitochondria::getStrength() const { return _strength; }

void Mitochondria::setEfficiency(const float efficiency) {
	if (efficiency >= 0.0 && efficiency <= 1.0)
		_efficiency = efficiency;
}
float Mitochondria::getEfficiency() const { return _efficiency; }

void Mitochondria::setConversionRate(const float conversionRate) {
	if (conversionRate > 0.0)
		_conversionRate = conversionRate;
}
float Mitochondria::getConversionRate() const { return _conversionRate; }

void Mitochondria::setActivationResource(const String activationResource) {
	if (activationResource == "nutrients" || activationResource == "energy")
		_activationResource = activationResource;
}
String Mitochondria::getActivationResource() const { return _activationResource; }

void Mitochondria::setThresholdType(const String thresholdType) {
	if (thresholdType == "high-pass" || thresholdType == "low-pass")
		_thresholdType = thresholdType;
}
String Mitochondria::getThresholdType() const { return _thresholdType; }

void Mitochondria::_ready() {
	AnimatedSprite2D *sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (sprite)
		this->setSprite(sprite);
}
