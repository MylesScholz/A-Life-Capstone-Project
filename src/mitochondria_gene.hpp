#pragma once

#include "gene.hpp"

using namespace godot;

class MitochondriaGene : public Gene {
public:
	MitochondriaGene(/* args */);
	~MitochondriaGene();

	String getType() override;
	String getName() override;
	CellStructure *express() override;
	float getValue() override;

	MitochondriaGene* clone() { return new MitochondriaGene(*this); }

private:
	/* data */
};