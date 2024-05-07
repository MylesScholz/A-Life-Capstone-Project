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
};

ModifierGene *boundedValueModifierGene(String, const float, const float, std::optional<const float>);

ModifierGene *discreteValueModifierGene(String, Vector<float>, std::optional<const float>);

ModifierGene *randomModifierGene();
