#include "gene.hpp"
#include "cell_structure.hpp"

void Gene::_bind_methods() {
}

Gene::Gene() {
}

Gene::~Gene() {
}

String Gene::getType() {
	return String();
}

String Gene::getName() {
	return String();
}

CellStructure *Gene::express() {
	return new CellStructure();
}

float Gene::getValue() {
	return 0.0f;
}
