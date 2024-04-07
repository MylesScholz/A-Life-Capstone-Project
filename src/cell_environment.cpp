#include "cell_environment.hpp"

void CellEnvironment::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_nutrient_zone_scene", "nutrient_zone_scene"), &CellEnvironment::setNutrientZoneScene);
	ClassDB::bind_method(D_METHOD("get_nutrient_zone_scene"), &CellEnvironment::getNutrientZoneScene);
	ClassDB::add_property("CellEnvironment", PropertyInfo(Variant::OBJECT, "nutrient_zone_scene"), "set_nutrient_zone_scene", "get_nutrient_zone_scene");

	ClassDB::bind_method(D_METHOD("set_n_nutrient_zones", "nutrient_zone_scene"), &CellEnvironment::setNNutrientZones);
	ClassDB::bind_method(D_METHOD("get_n_nutrient_zones"), &CellEnvironment::getNNutrientZones);
	ClassDB::add_property("CellEnvironment", PropertyInfo(Variant::INT, "n_nutrient_zones"), "set_n_nutrient_zones", "get_n_nutrient_zones");
}

CellEnvironment::CellEnvironment() {
	_nNutrientZones = 0;
}
CellEnvironment::~CellEnvironment() {}

void CellEnvironment::spawnNutrientZone() {
	// Create a random number generator
	RandomNumberGenerator rand = RandomNumberGenerator();

	// Instantiate the NutrientZone scene and cast it to a NutrientZone
	NutrientZone *nutrientZone = Object::cast_to<NutrientZone>(_nutrientZoneScene->instantiate());

	// Get viewport size for positioning
	Size2 viewportSize = get_viewport()->get_visible_rect().size;

	// Apply a random scaling to the NutrientZone
	nutrientZone->applyScale(rand.randf_range(0.5, 1.0));

	// Set the NutrientZone's position randomly in the viewport
	nutrientZone->set_position(Vector2(
			rand.randi_range(-viewportSize.x / 2, viewportSize.x / 2),
			rand.randi_range(-viewportSize.y / 2, viewportSize.y / 2)));

	// Add the NutrientZone as a child of this node
	this->add_child(nutrientZone);
}
void CellEnvironment::removeAllNutrientZones() {
	for (int i = this->get_child_count() - 1; i >= 0; i--) {
		Node *child = this->get_child(i);
		if (child->get_class() == "NutrientZone") {
			child->queue_free();
		}
	}
}

void CellEnvironment::setNutrientZoneScene(const Ref<PackedScene> nutrientZoneScene) { _nutrientZoneScene = nutrientZoneScene; }
Ref<PackedScene> CellEnvironment::getNutrientZoneScene() const { return _nutrientZoneScene; }

void CellEnvironment::setNNutrientZones(const int nNutrientZones) {
	if (nNutrientZones > 0 && nNutrientZones < 10)
		_nNutrientZones = nNutrientZones;
}
int CellEnvironment::getNNutrientZones() const { return _nNutrientZones; }