#include "modifier_gene.hpp"

ModifierGene::ModifierGene(String gene, float value) {
	geneName = gene;
    modifierValue = value;
}

ModifierGene::~ModifierGene() {
}

String ModifierGene::getType() { 
	return "Modifier";
}

String ModifierGene::getName() {
	return geneName;
}

CellStructure *ModifierGene::express() {
	return nullptr;
}

float ModifierGene::getValue() {
	return modifierValue;
}