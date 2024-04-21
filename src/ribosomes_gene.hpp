#pragma once

#include "gene.hpp"

using namespace godot;

class RibosomesGene : public Gene {
public:
	RibosomesGene(/* args */);
	~RibosomesGene();

	String getType() override;
	String getName() override;
	CellStructure *express() override;
	float getValue() override;

	RibosomesGene *clone() { return new RibosomesGene(*this); }

private:
	/* data */
};