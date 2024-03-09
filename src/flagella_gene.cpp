#include "flagella_gene.hpp"
#include "flagella.hpp"
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

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
	Ref<PackedScene> flagella_scene = ResourceLoader::get_singleton()->load("res://flagella.tscn");
	return Object::cast_to<Flagella>(flagella_scene->instantiate());
}

float FlagellaGene::getValue() {
	return 0.0f;
}
