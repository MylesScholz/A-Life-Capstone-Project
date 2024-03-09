#pragma once

#include "gene.hpp"


using namespace godot;

class FlagellaGene : public Gene
{
public:
    FlagellaGene(/* args */);
    ~FlagellaGene();

    String getType() override;
	String getName() override;
	CellStructure *express() override;
	float getValue() override;

private:
    /* data */

};
