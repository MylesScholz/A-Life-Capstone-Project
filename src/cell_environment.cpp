#include "cell_environment.hpp"

void CellEnvironment::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_nutrient_zone_scene", "nutrient_zone_scene"), &CellEnvironment::setNutrientZoneScene);
	ClassDB::bind_method(D_METHOD("get_nutrient_zone_scene"), &CellEnvironment::getNutrientZoneScene);
	ClassDB::add_property("CellEnvironment", PropertyInfo(Variant::OBJECT, "nutrient_zone_scene"), "set_nutrient_zone_scene", "get_nutrient_zone_scene");

	ClassDB::bind_method(D_METHOD("get_alive_count"), &CellEnvironment::GetAliveCount);
	ClassDB::bind_method(D_METHOD("get_nutrient_zone_count"), &CellEnvironment::GetNutrientZoneCount);

	ClassDB::bind_method(D_METHOD("set_n_nutrient_zones", "nutrient_zone_scene"), &CellEnvironment::setNNutrientZones);
	ClassDB::bind_method(D_METHOD("get_n_nutrient_zones"), &CellEnvironment::getNNutrientZones);
	ClassDB::add_property("CellEnvironment", PropertyInfo(Variant::INT, "n_nutrient_zones"), "set_n_nutrient_zones", "get_n_nutrient_zones");

	ClassDB::bind_method(D_METHOD("_on_cell_death"), &CellEnvironment::_on_cell_death);
	ADD_SIGNAL(MethodInfo("cell_death"));

	ClassDB::bind_method(D_METHOD("remove_all_nutrient_zones"), &CellEnvironment::removeAllNutrientZones);
	ClassDB::bind_method(D_METHOD("spawn_nutrient_zone"), &CellEnvironment::spawnNutrientZone);

	ClassDB::bind_method(D_METHOD("setNNutrientZones", "value"), &CellEnvironment::setNNutrientZones);
}

CellEnvironment::CellEnvironment() {
	_nNutrientZones = 0;
	_lineageGraph = LineageGraph();
}
CellEnvironment::~CellEnvironment() {}

int CellEnvironment::GetAliveCount() {
	int count = 0;
	for (int i = 0; i < this->get_child_count(); i++) {
		Node *child = this->get_child(i);
		if (Object::cast_to<Cell>(child)) {
			count++;
		}
	}
	return count;
}

int CellEnvironment::GetNutrientZoneCount() {
	int count = 0;
	for (int i = 0; i < this->get_child_count(); i++) {
		Node *child = this->get_child(i);
		if (Object::cast_to<NutrientZone>(child)) {
			count++;
		}
	}
	return count;
}

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
			rand.randi_range(0, viewportSize.x),
			rand.randi_range(0, viewportSize.y)));

	// Set to values from simulation parameters menu
	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->get_parent());

	SpinBox *NutrientMaximumSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Nutrient Zone/ScrollContainer/VBoxContainer/NutrientZoneNutrientMaximumContainer/SpinBox");
	nutrientZone->setNutrientMaximum(NutrientMaximumSpinBox->get_value());

	SpinBox *FeedingRateSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Nutrient Zone/ScrollContainer/VBoxContainer/FeedingRateContainer/SpinBox");
	nutrientZone->setFeedingRate(FeedingRateSpinBox->get_value());

	SpinBox *RegenerationRateSpinBox = spawner->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Nutrient Zone/ScrollContainer/VBoxContainer/RegenerationRateContainer/SpinBox");
	nutrientZone->setRegenerationRate(RegenerationRateSpinBox->get_value());

	Button *deleteStartingOnEmptyInput = spawner->get_node<Button>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Nutrient Zone/ScrollContainer/VBoxContainer/StartingNutrientZoneDelete");
	nutrientZone->setDeleteOnEmpty(deleteStartingOnEmptyInput->is_pressed());

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
	if (nNutrientZones > 0 && nNutrientZones <= 50)
		_nNutrientZones = nNutrientZones;
}
int CellEnvironment::getNNutrientZones() const { return _nNutrientZones; }

void CellEnvironment::addCell(Cell *cell) {
	this->add_child(cell);
	cell->connect("cell_death", Callable(this, "_on_cell_death"));

	_lineageGraph.addVertex(cell);
}
void CellEnvironment::removeCell(Cell *cell) {
	_lineageGraph.removeVertex(cell);

	cell->resetCollisions();
	cell->queue_free();
}
LineageGraph *CellEnvironment::getLineageGraph() { return &_lineageGraph; }

void CellEnvironment::_on_cell_death(Cell *cell) {
	// Disable Cell physics
	cell->set_disable_mode(cell->DISABLE_MODE_REMOVE);
	cell->set_process_mode(cell->PROCESS_MODE_DISABLED);

	// Store Cell position for placing the NutrientZone
	Vector2 cellPosition = cell->get_position();

	// Move Cell outside the CellEnvironment bounds for storage
	_lineageGraph.storeCell(cell);
	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->get_parent());
	cell->reparent(spawner->get_node<SubViewport>("UI/StatsPanel/TabContainer/Lineage/SubViewportContainer/SubViewport"));

	CellState *cellState = cell->get_node<CellState>("CellState");
	if (cellState->getTotalNutrients() <= 0)
		return;

	// Instantiate the NutrientZone scene and cast it to a NutrientZone
	NutrientZone *nutrientZone = Object::cast_to<NutrientZone>(_nutrientZoneScene->instantiate());

	// Apply a scaling to the NutrientZone approximately proportional to the dead cell
	nutrientZone->applyScale(cell->getScale() / 4);

	// Set the NutrientZone's position in the same position as the dead cell
	nutrientZone->set_position(cellPosition);

	// Set the NutrientZone to delete itself when it runs out of nutrients
	nutrientZone->setDeleteOnEmpty(true);

	// Set the NutrientZone's total nutrients to the dead cell's total nutrients and not to regenerate
	nutrientZone->setTotalNutrients(cellState->getTotalNutrients());
	nutrientZone->setRegenerationRate(0.0);

	// Add the NutrientZone as a child of this node
	this->add_child(nutrientZone);
}

void CellEnvironment::_ready() {
	DONT_RUN_IN_EDITOR;

	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));

	// Connect to values from simulation parameters menu
	Node *NStartingNutrientZonesSpinBox = spawner->get_node<Node>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Nutrient Zone/ScrollContainer/VBoxContainer/NNutrientZoneContainer/SpinBox");
	NStartingNutrientZonesSpinBox->connect("value_changed", Callable(this, "setNNutrientZones"));
}