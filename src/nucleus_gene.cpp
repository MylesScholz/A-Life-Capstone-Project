#include "nucleus_gene.hpp"
#include "nucleus.hpp"

NucleusGene::NucleusGene() {
}

NucleusGene::~NucleusGene() {
}

String NucleusGene::getType() {
	return "Structure";
}

String NucleusGene::getName() {
	return "Nucleus";
}

CellStructure *NucleusGene::express() {
	return new Nucleus();
}

float NucleusGene::getValue() {
	return 0.0f;
}
