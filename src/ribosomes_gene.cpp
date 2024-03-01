#include "ribosomes_gene.hpp"
#include "ribosomes.hpp"

RibosomesGene::RibosomesGene() {
}

RibosomesGene::~RibosomesGene() {
}

String RibosomesGene::getType() {
	return "Structure";
}

String RibosomesGene::getName() {
	return "Ribosomes";
}

CellStructure *RibosomesGene::express() {
	return new Ribosomes();
}

float RibosomesGene::getValue() {
	return 0.0f;
}