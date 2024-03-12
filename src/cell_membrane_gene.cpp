#include "cell_membrane_gene.hpp"

CellMembraneGene::CellMembraneGene() {}
CellMembraneGene::~CellMembraneGene() {}

String CellMembraneGene::getType() { return "Structure"; }
String CellMembraneGene::getName() { return "CellMembrane"; }

CellStructure *CellMembraneGene::express() {
	Ref<PackedScene> cell_membrane_scene = ResourceLoader::get_singleton()->load("res://cell_membrane.tscn");
	return Object::cast_to<CellMembrane>(cell_membrane_scene->instantiate());
}

float CellMembraneGene::getValue() { return 0; }