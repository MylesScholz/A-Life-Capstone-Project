#include "flagella_gene.hpp"
#include "flagella.hpp"

FlagellaGene::FlagellaGene() {
}

FlagellaGene::~FlagellaGene() {
}

String FlagellaGene::getType() {
	return "Structure";
}

String FlagellaGene::getName() {
	return "Flagella";
}

CellStructure *FlagellaGene::express() {
	return new Flagella();
}

float FlagellaGene::getValue() {
	return 0.0f;
}
