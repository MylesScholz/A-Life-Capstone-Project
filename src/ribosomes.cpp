#include "ribosomes.hpp"
#include "cell_spawner.hpp"

#include "helpers.hpp"

#include <godot_cpp/classes/option_button.hpp>
#include <godot_cpp/classes/spin_box.hpp>

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

	ClassDB::bind_method(D_METHOD("set_preferred_conversion_rate", "preferred_conversion_rate"), &Ribosomes::setPreferredConversionRate);
	ClassDB::bind_method(D_METHOD("get_preferred_conversion_rate"), &Ribosomes::getPreferredConversionRate);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::FLOAT, "preferred_conversion_rate"), "set_preferred_conversion_rate", "get_preferred_conversion_rate");

	ClassDB::bind_method(D_METHOD("set_activation_resource", "activation_resource"), &Ribosomes::setActivationResource);
	ClassDB::bind_method(D_METHOD("get_activation_resource"), &Ribosomes::getActivationResource);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::STRING, "activation_resource"), "set_activation_resource", "get_activation_resource");

	ClassDB::bind_method(D_METHOD("set_threshold_type", "threshold_type"), &Ribosomes::setThresholdType);
	ClassDB::bind_method(D_METHOD("get_threshold_type"), &Ribosomes::getThresholdType);
	ClassDB::add_property("Ribosomes", PropertyInfo(Variant::STRING, "threshold_type"), "set_threshold_type", "get_threshold_type");
}

Ribosomes::Ribosomes() {
	// Ribosomes attributes
	_activationThreshold = 0.5;
	_strength = 1.0;
	_efficiency = 1.0;
	_preferredConversionRate = 1.0;
	_activationResource = "nutrients";
	_thresholdType = "low-pass";
}
Ribosomes::~Ribosomes() {}

void Ribosomes::activate(CellState *cellState) {
	if (this->getSprite()->get_frame() == this->getSprite()->get_sprite_frames()->get_frame_count("activate") - 1)
		this->getSprite()->stop();

	// If the nutrient:energy conversion rate is not set (-1 by default), set it to these Ribosomes' preferred value
	if (cellState->getNutrientEnergyConversionRate() == -1)
		cellState->setNutrientEnergyConversionRate(_preferredConversionRate);

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
		cellState->incrementTotalNutrients(_efficiency * cellState->getNutrientEnergyConversionRate() * _strength);

		this->getSprite()->set_frame(1);
		this->getSprite()->play("activate");
	}
}

void Ribosomes::modify(String modifierName, float modifierValue) {
	/*
	 * Relevant ModifierGenes
	 * ACTIVATION_THRESHOLD: sets _activationThreshold
	 * STRENGTH: sets _strength
	 * CONVERSION_RATE: sets _preferredConversionRate
	 * ACTIVATION_RESOURCE: sets _activationResource (0 -> "nutrients", 1 -> "energy")
	 * THRESHOLD_TYPE: sets _thresholdType (0 -> "low-pass", 1 -> "high-pass")
	 */

	if (modifierName == "ACTIVATION_THRESHOLD") {
		setActivationThreshold(modifierValue);
	} else if (modifierName == "STRENGTH") {
		setStrength(modifierValue);
	} else if (modifierName == "CONVERSION_RATE") {
		setPreferredConversionRate(modifierValue);
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

void Ribosomes::setPreferredConversionRate(const float preferredConversionRate) {
	if (preferredConversionRate > 0.0)
		_preferredConversionRate = preferredConversionRate;
}
float Ribosomes::getPreferredConversionRate() const { return _preferredConversionRate; }

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
	DONT_RUN_IN_EDITOR;
	AnimatedSprite2D *sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (sprite)
		this->setSprite(sprite);

	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));
	// Set to values from simulation parameters menu
	SpinBox *activationThresholdSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/activationThreshold/SpinBox");
	this->setActivationThreshold(activationThresholdSpinBox->get_value());

	SpinBox *strengthSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/strength/SpinBox");
	this->setStrength(strengthSpinBox->get_value());

	SpinBox *efficiencySpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/efficiency/SpinBox");
	this->setEfficiency(efficiencySpinBox->get_value());

	SpinBox *preferredConversionRateSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/preferredConversionRate/SpinBox");
	this->setPreferredConversionRate(preferredConversionRateSpinBox->get_value());

	OptionButton *activationResourceOptionButton = spawner->get_node<OptionButton>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/activationResource/OptionButton");
	this->setActivationResource(activationResourceOptionButton->get_item_text(activationResourceOptionButton->get_selected()));

	OptionButton *thresholdTypeOptionButton = spawner->get_node<OptionButton>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/thresholdType/OptionButton");
	this->setThresholdType(thresholdTypeOptionButton->get_item_text(thresholdTypeOptionButton->get_selected()));

	SpinBox *creationNutrientCostSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/creationNutrientCost/SpinBox");
	this->setCreationNutrientCost(creationNutrientCostSpinBox->get_value());

	SpinBox *creationEnergyCostSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/creationEnergyCost/SpinBox");
	this->setCreationEnergyCost(creationEnergyCostSpinBox->get_value());

	SpinBox *maintenanceNutrientCostSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/maintenanceNutrientCost/SpinBox");
	this->setMaintenanceNutrientCost(maintenanceNutrientCostSpinBox->get_value());

	SpinBox *maintenanceEnergyCostSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/InitalValues/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/maintenanceEnergyCost/SpinBox");
	this->setMaintenanceEnergyCost(maintenanceEnergyCostSpinBox->get_value());
}
