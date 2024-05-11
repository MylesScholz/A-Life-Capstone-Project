#include "cell_environment.hpp"

void CellEnvironment::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_nutrient_zone_scene", "nutrient_zone_scene"), &CellEnvironment::setNutrientZoneScene);
	ClassDB::bind_method(D_METHOD("get_nutrient_zone_scene"), &CellEnvironment::getNutrientZoneScene);
	ClassDB::add_property("CellEnvironment", PropertyInfo(Variant::OBJECT, "nutrient_zone_scene"), "set_nutrient_zone_scene", "get_nutrient_zone_scene");

	ClassDB::bind_method(D_METHOD("set_n_nutrient_zones", "nutrient_zone_scene"), &CellEnvironment::setNNutrientZones);
	ClassDB::bind_method(D_METHOD("get_n_nutrient_zones"), &CellEnvironment::getNNutrientZones);
	ClassDB::add_property("CellEnvironment", PropertyInfo(Variant::INT, "n_nutrient_zones"), "set_n_nutrient_zones", "get_n_nutrient_zones");

	ClassDB::bind_method(D_METHOD("_on_cell_death"), &CellEnvironment::_on_cell_death);
	ADD_SIGNAL(MethodInfo("cell_death"));

	ClassDB::bind_method(D_METHOD("remove_all_nutrient_zones"), &CellEnvironment::removeAllNutrientZones);
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
	if (nNutrientZones > 0 && nNutrientZones < 50)
		_nNutrientZones = nNutrientZones;
}
int CellEnvironment::getNNutrientZones() const { return _nNutrientZones; }

void CellEnvironment::_on_cell_death(Cell *cell) {
	// Clear Cell selection
	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->get_parent());
	Stats *stats = spawner->get_node<Stats>("UI/StatsPanel/TabContainer/Stats");
	if (cell == stats->get_selected_cell())
		stats->_clear_selected_cell();

	// Instantiate the NutrientZone scene and cast it to a NutrientZone
	NutrientZone *nutrientZone = Object::cast_to<NutrientZone>(_nutrientZoneScene->instantiate());

	// Get viewport size for positioning
	Size2 viewportSize = get_viewport()->get_visible_rect().size;

	// Apply a scaling to the NutrientZone approximately proportional to the dead cell
	nutrientZone->applyScale(cell->getScale() / 4);

	// Set the NutrientZone's position in the same position as the dead cell
	godot::Vector2 cellPosition = cell->get_position();
	Vector2 nutrientZonePosition = Vector2(cellPosition.x - viewportSize.x / 2, cellPosition.y - viewportSize.y / 2);
	nutrientZone->set_position(nutrientZonePosition);

	// Set the NutrientZone to delete itself when it runs out of nutrients
	nutrientZone->setDeleteOnEmpty(true);

	// Set the NutrientZone's total nutrients to the dead cell's total nutrients and not to regenerate
	CellState *cellState = cell->get_node<CellState>("CellState");
	nutrientZone->setTotalNutrients(cellState->getTotalNutrients());
	nutrientZone->setRegenerationRate(0.0);

	// Add the NutrientZone as a child of this node
	this->add_child(nutrientZone);
}