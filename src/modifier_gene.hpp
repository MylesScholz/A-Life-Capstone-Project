#pragma once

#include "gene.hpp"

#include <godot_cpp/classes/random_number_generator.hpp>
#include <optional>

using namespace godot;

class ModifierGene : public Gene {
public:
	ModifierGene(String gene, float value);
	~ModifierGene();

	String getType() override;
	String getName() override;
	CellStructure *express() override;
	float getValue() override;

private:
	float _modifierValue;
	String _geneName;
};

Vector<String> modifierGeneTypes = {
	"ACTIVATION_THRESHOLD",
	"STRENGTH",
	"CONVERSION_RATE",
	"ACTIVATION_RESOURCE",
	"THRESHOLD_TYPE"
};

ModifierGene boundedValueModifierGene(String name, const float min, const float max, std::optional<const float> value = std::nullopt) {
	if (value.has_value() && *value >= min && *value <= max)
		return ModifierGene(name, *value);

	RandomNumberGenerator rand = RandomNumberGenerator();
	return ModifierGene(name, rand.randf_range(min, max));
}

ModifierGene discreteValueModifierGene(String name, Vector<float> values, std::optional<const float> value = std::nullopt) {
	if (value.has_value() && values.find(*value) != -1)
		return ModifierGene(name, *value);

	RandomNumberGenerator rand = RandomNumberGenerator();
	return ModifierGene(name, values[rand.randi_range(0, values.size() - 1)]);
}

ModifierGene randomModifierGene() {
	RandomNumberGenerator rand = RandomNumberGenerator();
	String randType = modifierGeneTypes[rand.randi_range(0, modifierGeneTypes.size() - 1)];

	// A Vector of valid values for binary value ModifierGenes (e.g., THRESHOLD_TYPE)
	Vector<float> binaryValues = Vector<float>();
	binaryValues.push_back(0.0);
	binaryValues.push_back(1.0);

	if (randType == "ACTIVATION_THRESHOLD") {
		return boundedValueModifierGene(randType, 0, 1);
	}
	if (randType == "STRENGTH") {
		return boundedValueModifierGene(randType, 0, 10);
	}
	if (randType == "CONVERSION_RATE") {
		return boundedValueModifierGene(randType, 0, 10);
	}
	if (randType == "ACTIVATION_RESOURCE") {
		return discreteValueModifierGene(randType, binaryValues);
	}
	if (randType == "THRESHOLD_TYPE") {
		return discreteValueModifierGene(randType, binaryValues);
	}

	// Reaching this point should be impossible, but for safety, return a dummy ModifierGene
	return ModifierGene("NONE", 0.0);
}
