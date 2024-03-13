#pragma once

#include "gene.hpp"

using namespace godot;

class NucleusGene : public Gene {
public:
	NucleusGene(/* args */);
	~NucleusGene();

	String getType() override;
	String getName() override;
	CellStructure *express() override;
	float getValue() override;

private:
	/* data */
};