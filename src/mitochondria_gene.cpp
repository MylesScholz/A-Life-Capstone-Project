#include "mitochondria_gene.hpp"
#include "mitochondria.hpp"
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

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
	Ref<PackedScene> mitochondria_scene = ResourceLoader::get_singleton()->load("res://mitochondria.tscn");
	return Object::cast_to<Mitochondria>(mitochondria_scene->instantiate());
}

float MitochondriaGene::getValue() {
	return 0.0f;
}