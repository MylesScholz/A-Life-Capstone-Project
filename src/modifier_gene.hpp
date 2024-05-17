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

	ModifierGene *clone() { return new ModifierGene(*this); }

private:
	float _modifierValue;
	String _geneName;

	String _modifierGeneTypes[7] = {
		"ACTIVATION_THRESHOLD",
		"STRENGTH",
		"CONVERSION_RATE",
		"GROWTH_CAP",
		"ACTIVATION_RESOURCE",
		"THRESHOLD_TYPE",
		"N_SUBSTRUCTURES"
	};
};

ModifierGene *boundedValueModifierGene(String, const float, const float, std::optional<const float>);

ModifierGene *discreteValueModifierGene(String, Vector<float>, std::optional<const float>);

ModifierGene *randomModifierGene();
