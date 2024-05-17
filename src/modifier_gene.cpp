#include "modifier_gene.hpp"

ModifierGene::ModifierGene(String gene, float value) {
	_geneName = gene;
	_modifierValue = value;
}

ModifierGene::~ModifierGene() {
}

String ModifierGene::getType() {
	return "Modifier";
}

String ModifierGene::getName() {
	return _geneName;
}

CellStructure *ModifierGene::express() {
	return nullptr;
}

float ModifierGene::getValue() {
	return _modifierValue;
}

ModifierGene *boundedValueModifierGene(String name, const float min, const float max, std::optional<const float> value = std::nullopt) {
	if (value.has_value() && *value >= min && *value <= max)
		return new ModifierGene(name, *value);

	RandomNumberGenerator rand = RandomNumberGenerator();
	return new ModifierGene(name, rand.randf_range(min, max));
}

ModifierGene *discreteValueModifierGene(String name, Vector<float> values, std::optional<const float> value = std::nullopt) {
	if (value.has_value() && values.find(*value) != -1)
		return new ModifierGene(name, *value);

	RandomNumberGenerator rand = RandomNumberGenerator();
	return new ModifierGene(name, values[rand.randi_range(0, values.size() - 1)]);
}

ModifierGene *randomModifierGene() {
	String modifierGeneTypes[] = {
		"ACTIVATION_THRESHOLD",
		"STRENGTH",
		"CONVERSION_RATE",
		"GROWTH_CAP",
		"ACTIVATION_RESOURCE",
		"THRESHOLD_TYPE",
		"N_SUBSTRUCTURES",
		"CHANCE"
	};
	const int nModifierGeneTypes = sizeof(modifierGeneTypes) / sizeof(modifierGeneTypes[0]);

	RandomNumberGenerator rand = RandomNumberGenerator();

	String randType = modifierGeneTypes[rand.randi_range(0, nModifierGeneTypes - 1)];

	// A Vector of valid values for binary value ModifierGenes (e.g., THRESHOLD_TYPE)
	Vector<float> binaryValues = Vector<float>();
	binaryValues.push_back(0.0);
	binaryValues.push_back(1.0);

	// A Vector of valid values for N_SUBSTRUCTURES ModifierGenes (ints 1-10)
	Vector<float> substructureValues = Vector<float>();
	for (int i = 1; i <= 10; i++) {
		substructureValues.push_back(i);
	}

	if (randType == "ACTIVATION_THRESHOLD") {
		return boundedValueModifierGene(randType, 0, 1);
	}
	if (randType == "STRENGTH") {
		return boundedValueModifierGene(randType, 0, 10);
	}
	if (randType == "CONVERSION_RATE") {
		return boundedValueModifierGene(randType, 0, 10);
	}
	if (randType == "GROWTH_CAP") {
		return boundedValueModifierGene(randType, 0.25, 1);
	}
	if (randType == "ACTIVATION_RESOURCE") {
		return discreteValueModifierGene(randType, binaryValues);
	}
	if (randType == "THRESHOLD_TYPE") {
		return discreteValueModifierGene(randType, binaryValues);
	}
	if (randType == "N_SUBSTRUCTURES") {
		return discreteValueModifierGene(randType, substructureValues);
	}
	if (randType == "CHANCE") {
		return boundedValueModifierGene(randType, 0, 1);
	}

	// Reaching this point should be impossible, but for safety, return a dummy ModifierGene
	return new ModifierGene("NONE", 0.0);
}
