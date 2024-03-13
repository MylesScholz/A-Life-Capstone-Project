#pragma once

#include "gene.hpp"

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
	float modifierValue;
	String geneName;
};