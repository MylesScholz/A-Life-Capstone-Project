#include "mitochondria_gene.hpp"
#include "mitochondria.hpp"

MitochondriaGene::MitochondriaGene() {
}

MitochondriaGene::~MitochondriaGene() {
}

String MitochondriaGene::getType() {
	return "Structure";
}

String MitochondriaGene::getName() {
	return "Mitochondria";
}

CellStructure *MitochondriaGene::express() {
	return new Mitochondria();
}

float MitochondriaGene::getValue() {
	return 0.0f;
}