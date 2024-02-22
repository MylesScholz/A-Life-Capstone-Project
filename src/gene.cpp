#include "gene.hpp"
#include "cell_structure.hpp"

void godot::Gene::_bind_methods() {
}

godot::Gene::Gene() {
}

godot::Gene::~Gene() {
}

std::string godot::Gene::getType() {
	return std::string();
}

std::string godot::Gene::getName() {
	return std::string();
}

CellStructure* godot::Gene::express() {
	return new CellStructure();
}

float godot::Gene::getValue() {
	return 0.0f;
}
