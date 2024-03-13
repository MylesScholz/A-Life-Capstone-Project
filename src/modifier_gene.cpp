#include "modifier_gene.hpp"

ModifierGene::ModifierGene(String gene, float value) {
	_geneName = gene;
	_modifierValue = value;
}

ModifierGene::~ModifierGene() {
}

String ModifierGene::getType() {
	return "Modifier";
}

String ModifierGene::getName() {
	return _geneName;
}

CellStructure *ModifierGene::express() {
	return nullptr;
}

float ModifierGene::getValue() {
	return _modifierValue;
}
