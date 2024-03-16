#pragma once

#include "cell_membrane.hpp"
#include "gene.hpp"

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

class CellMembraneGene : public Gene {
public:
	CellMembraneGene();
	~CellMembraneGene();

	String getType() override;
	String getName() override;
	CellStructure *express() override;
	float getValue() override;

private:
	/* Attributes */
};