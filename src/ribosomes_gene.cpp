#include "ribosomes_gene.hpp"
#include "ribosomes.hpp"
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

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
    Ref<PackedScene> ribosomes_scene = ResourceLoader::get_singleton()->load("res://ribosomes.tscn");
	return Object::cast_to<Ribosomes>(ribosomes_scene->instantiate());
}

float RibosomesGene::getValue() {
	return 0.0f;
}