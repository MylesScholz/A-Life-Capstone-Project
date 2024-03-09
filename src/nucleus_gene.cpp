#include "nucleus_gene.hpp"
#include "nucleus.hpp"
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

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
	Ref<PackedScene> nucleus_scene = ResourceLoader::get_singleton()->load("res://nucleus.tscn");
	return Object::cast_to<Nucleus>(nucleus_scene->instantiate());
}

float NucleusGene::getValue() {
	return 0.0f;
}
