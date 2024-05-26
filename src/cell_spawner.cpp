#include "cell_spawner.hpp"
#include "cell.hpp"
#include "cell_environment.hpp"
#include "genome.hpp"
#include "stats.hpp"

#include <godot_cpp/core/class_db.hpp>

#include "helpers.hpp"

// These includes are for starting testing and should stay with the class we're using as the project entry point
#ifdef TESTS_ENABLED
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <string>
#include <vector>

#include "test_main.hpp"
#endif

using namespace godot;

void CellSpawner::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_num_cells", "num_cells"), &CellSpawner::setNumCells);
	ClassDB::bind_method(D_METHOD("get_num_cells"), &CellSpawner::getNumCells);

	ClassDB::add_property("CellSpawner", PropertyInfo(Variant::INT, "num_cells"), "set_num_cells", "get_num_cells");

	ClassDB::bind_method(D_METHOD("set_cell_scene", "cell_scene"), &CellSpawner::setCellScene);
	ClassDB::bind_method(D_METHOD("get_cell_scene"), &CellSpawner::getCellScene);
	ClassDB::add_property("CellSpawner", PropertyInfo(Variant::OBJECT, "cell_scene"), "set_cell_scene", "get_cell_scene");

	ClassDB::bind_method(D_METHOD("set_min_force", "min_force"), &CellSpawner::setMinForce);
	ClassDB::bind_method(D_METHOD("get_min_force"), &CellSpawner::getMinForce);
	ClassDB::add_property("CellSpawner", PropertyInfo(Variant::INT, "min_force"), "set_min_force", "get_min_force");

	ClassDB::bind_method(D_METHOD("set_max_force", "max_force"), &CellSpawner::setMaxForce);
	ClassDB::bind_method(D_METHOD("get_max_force"), &CellSpawner::getMaxForce);
	ClassDB::add_property("CellSpawner", PropertyInfo(Variant::INT, "max_force"), "set_max_force", "get_max_force");

	ClassDB::bind_method(D_METHOD("set_resource_proportion", "resource_proportion"), &CellSpawner::setResourceProportion);
	ClassDB::bind_method(D_METHOD("get_resource_proportion"), &CellSpawner::getResourceProportion);
	ClassDB::add_property("CellSpawner", PropertyInfo(Variant::FLOAT, "resource_proportion"), "set_resource_proportion", "get_resource_proportion");

	ClassDB::bind_method(D_METHOD("remove_all_cells"), &CellSpawner::removeAllCells);

	ClassDB::bind_method(D_METHOD("_on_cell_reproduction", "cell"), &CellSpawner::_on_cell_reproduction);
	ADD_SIGNAL(MethodInfo("cell_reproduction", PropertyInfo(Variant::OBJECT, "cell")));

	ADD_SIGNAL(MethodInfo("cell_selected", PropertyInfo(Variant::OBJECT, "cell")));

	ClassDB::bind_method(D_METHOD("spawn_cell", "isImmortal"), &CellSpawner::spawnCell);

	ClassDB::bind_method(D_METHOD("setNumCells", "value"), &CellSpawner::setNumCells);

	ClassDB::bind_method(D_METHOD("setResourceProportion", "value"), &CellSpawner::setResourceProportion);
}

CellSpawner::CellSpawner() {}
CellSpawner::~CellSpawner() {
	// Clean up spawned child nodes
	queue_free();
}

void CellSpawner::setCellScene(const Ref<PackedScene> cellScene) {
	_cellScene = cellScene;
}
Ref<PackedScene> CellSpawner::getCellScene() const { return _cellScene; }

void CellSpawner::setNumCells(const int numCells) { _numCells = numCells; }
int CellSpawner::getNumCells() const { return _numCells; }

void CellSpawner::setMinForce(const float minForce) {
	if (minForce > _maxForce) {
		_minForce = _maxForce;
	} else {
		_minForce = minForce;
	}
}
float CellSpawner::getMinForce() const { return _minForce; }

void CellSpawner::setMaxForce(const float maxForce) {
	if (maxForce < _minForce) {
		_maxForce = _minForce;
	} else {
		_maxForce = maxForce;
	}
}
float CellSpawner::getMaxForce() const { return _maxForce; }

void CellSpawner::setResourceProportion(const float resourceProportion) {
	if (resourceProportion >= 0 && resourceProportion <= 1)
		_resourceProportion = resourceProportion;
}
float CellSpawner::getResourceProportion() const { return _resourceProportion; }

void CellSpawner::spawnCell(bool isImmortal) {
	// Create a RandomNumberGenerator object
	RandomNumberGenerator rand = RandomNumberGenerator();

	// Instantiate cell scene
	Node *cell = _cellScene->instantiate();
	// Get viewport size for positioning
	Size2 viewportSize = get_viewport()->get_visible_rect().size;
	// Cast cell scene to Cell object for ease of use
	Cell *cellObject = Object::cast_to<Cell>(cell);

	CellEnvironment *cellEnvironment = this->get_node<CellEnvironment>("CellEnvironment");
	cellEnvironment->addCell(cellObject);

	// Set Cell size
	cellObject->applyScale(rand.randf_range(0.25, 1));
	Size2 cellSize = cellObject->getSpriteSize();

	// Set Cell resources to _resourceProportion of their maxima
	CellState *cellState = cellObject->get_node<CellState>("CellState");
	cellState->setTotalNutrients(_resourceProportion * cellState->getNutrientMaximum());
	cellState->setTotalEnergy(_resourceProportion * cellState->getEnergyMaximum());

	// Set to values from simulation parameters menu
	SpinBox *GrowthRateSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell/ScrollContainer/VBoxContainer/GrowthRateContainer/SpinBox");
	cellState->setGrowthRate(GrowthRateSpinBox->get_value());

	SpinBox *LifeSpanSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell/ScrollContainer/VBoxContainer/CellLifespanContainer/SpinBox");
	cellState->setLifespan(LifeSpanSpinBox->get_value());

	SpinBox *GrowthNutrientCostSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell/ScrollContainer/VBoxContainer/GrowthNutrientCostContainer/SpinBox");
	cellState->setGrowthNutrientCost(GrowthNutrientCostSpinBox->get_value());

	SpinBox *GrowthEnergyCostSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell/ScrollContainer/VBoxContainer/GrowthEnergyCostContainer/SpinBox");
	cellState->setGrowthEnergyCost(GrowthEnergyCostSpinBox->get_value());

	SpinBox *mutationChanceSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell/ScrollContainer/VBoxContainer/MutationChanceContainer/SpinBox");
	cellState->addMutationChance(mutationChanceSpinBox->get_value());

	// Set gene probabilities from sim parameters
	SpinBox *cellMembraneMutationChanceMinSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell Membrane/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMin");
	SpinBox *cellMembraneMutationChanceMaxSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell Membrane/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMax");
	cellObject->getGenome()->setCellMembraneChance(cellMembraneMutationChanceMinSpinBox->get_value(), cellMembraneMutationChanceMaxSpinBox->get_value());

	SpinBox *flagellaMutationChanceMinSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Flagella/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMin");
	SpinBox *flagellaMutationChanceMaxSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Flagella/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMax");
	cellObject->getGenome()->setFlagellaChance(flagellaMutationChanceMinSpinBox->get_value(), flagellaMutationChanceMaxSpinBox->get_value());

	SpinBox *mitochondriaMutationChanceMinSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Mitochondria/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMin");
	SpinBox *mitochondriaMutationChanceMaxSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Mitochondria/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMax");
	cellObject->getGenome()->setMitochondriaChance(mitochondriaMutationChanceMinSpinBox->get_value(), mitochondriaMutationChanceMaxSpinBox->get_value());

	SpinBox *nucleusMutationChanceMinSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Nucleus/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMin");
	SpinBox *nucleusMutationChanceMaxSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Nucleus/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMax");
	cellObject->getGenome()->setNucleusChance(nucleusMutationChanceMinSpinBox->get_value(), nucleusMutationChanceMaxSpinBox->get_value());

	SpinBox *ribosomeMutationChanceMinSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMin");
	SpinBox *ribosomeMutationChanceMaxSpinBox = this->get_node<SpinBox>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Ribosomes/ScrollContainer/VBoxContainer/mutationChanceRange/SpinBoxMax");
	cellObject->getGenome()->setRibosomeChance(ribosomeMutationChanceMinSpinBox->get_value(), ribosomeMutationChanceMaxSpinBox->get_value());

	// Set Cell position to random location in viewport
	cellObject->set_global_position(Vector2(
			rand.randi_range(cellSize.x / 4, viewportSize.x - cellSize.x / 4),
			rand.randi_range(cellSize.y / 4, viewportSize.y - cellSize.y / 4)));

	// Apply random initial force to Cell
	float force_magnitude = rand.randf_range(_minForce, _maxForce);
	float direction = rand.randf_range(0, 2 * Math_PI);
	Vector2 force = Vector2(0, -1).rotated(direction) * force_magnitude;
	cellObject->apply_force(force);

	cellObject->apply_torque(rand.randf_range(-500, 500));

	// Prevent display cells from dying
	cellObject->setImmortal(isImmortal);

	if (!isImmortal)
		cellObject->get_node<Nucleus>("Nucleus")->connect("cell_reproduction", Callable(this, "_on_cell_reproduction"));

	/*StatsCounter *statsCounter = this->get_node<StatsCounter>("UI/StatsPanel/StatsCounter");
	cellObject->connect("cell_selected", Callable(statsCounter, "_update_Stats"));*/
}

void CellSpawner::_on_cell_reproduction(Cell *cell) {
	// Create a RandomNumberGenerator object
	RandomNumberGenerator rand = RandomNumberGenerator();

	Node *childCell = _cellScene->instantiate();
	Node *secondCell = _cellScene->instantiate();
	Cell *cellObject = Object::cast_to<Cell>(childCell);
	Cell *secondObject = Object::cast_to<Cell>(secondCell);

	cellObject->seteq(cell);
	secondObject->seteq(cell);

	cellObject->set_position(cell->get_position());
	secondObject->set_position(cell->get_position());

	// This probably shouldn't be random for a child cell, and I assume w/ the flagella rework it won't be
	float force_magnitude = rand.randf_range(_minForce, _maxForce);
	float direction = rand.randf_range(0, 2 * Math_PI);
	Vector2 force = Vector2(0, -1).rotated(direction) * force_magnitude;
	cellObject->apply_force(force);

	force_magnitude = rand.randf_range(_minForce, _maxForce);
	direction = rand.randf_range(0, 2 * Math_PI);
	force = Vector2(0, -1).rotated(direction) * force_magnitude;
	secondObject->apply_force(force);

	cellObject->apply_torque(rand.randf_range(-500, 500));
	secondObject->apply_torque(rand.randf_range(-500, 500));

	CellEnvironment *cellEnvironment = this->get_node<CellEnvironment>("CellEnvironment");
	cellEnvironment->addCell(cellObject);
	cellEnvironment->getLineageGraph()->addEdge(cell, cellObject);

	cellEnvironment->addCell(secondObject);
	cellEnvironment->getLineageGraph()->addEdge(cell, secondObject);

	// Split the parent Cell's area evenly between the parent and the child
	float halfArea = (sqrt(2) / 2);
	cell->applyScale(halfArea);
	cellObject->applyScale(cell->getScale());
	secondObject->applyScale(cell->getScale());

	//Kill the Parent cell once its created the 2 child cells
	CellState *cellState = cell->get_node<CellState>("CellState");
	cellState->setTotalEnergy(0.0);
	cellState->setTotalNutrients(0.0);
	cell->emit_signal("cell_death", cell);
	cell->clearStatsOnDeath(cell);

	// Check for Nuclei and if present, attach reproduction signal
	Nucleus *nucleus = cellObject->get_node<Nucleus>("Nucleus");
	if (nucleus)
		nucleus->connect("cell_reproduction", Callable(this, "_on_cell_reproduction"));
	nucleus = secondObject->get_node<Nucleus>("Nucleus");
	if (nucleus)
		nucleus->connect("cell_reproduction", Callable(this, "_on_cell_reproduction"));
}

void CellSpawner::removeAllCells() {
	CellEnvironment *cellEnvironment = this->get_node<CellEnvironment>("CellEnvironment");

	for (int i = cellEnvironment->get_child_count() - 1; i >= 0; i--) {
		Node *child = cellEnvironment->get_child(i);

		if (child->get_class() == "Cell") {
			Cell *cell = Object::cast_to<Cell>(child);
			cellEnvironment->removeCell(cell);
		}
	}

	SubViewport *subViewport = this->get_node<SubViewport>("UI/StatsPanel/TabContainer/Lineage/SubViewportContainer/SubViewport");

	for (int i = subViewport->get_child_count() - 1; i >= 0; i--) {
		Node *child = subViewport->get_child(i);

		if (child->get_class() == "Cell") {
			Cell *cell = Object::cast_to<Cell>(child);
			subViewport->remove_child(cell);
			cellEnvironment->removeCell(cell);
		}
	}
}

void CellSpawner::_ready() {
	DONT_RUN_IN_EDITOR;

	// If tests are enabled, check for custom cmdline arg to run tests,
	// forwarding additional user args into doctest as its args
#ifdef TESTS_ENABLED
	for (auto arg : OS::get_singleton()->get_cmdline_args()) {
		if (arg == "--runTests" || arg == "-T") {
			// Collect user command line args to pass into doctest
			std::vector<const char *> userArgs;
			for (godot::String arg : OS::get_singleton()->get_cmdline_user_args()) {
				const char *charArg = arg.ascii().get_data();
				userArgs.push_back(charArg);
			}

			// Run the tests, exit, and return the value doctest returned
			int retVal = doctest_run(userArgs.size(), userArgs.data());
			get_tree()->quit(retVal);
		}
	}
#endif

	// Connect to values from simulation parameters menu
	Node *NumberOfStartingCellsSpinBox = this->get_node<Node>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell/ScrollContainer/VBoxContainer/NStartingCellsContainer/SpinBox");
	NumberOfStartingCellsSpinBox->connect("value_changed", Callable(this, "setNumCells"));

	Node *ResourceProportionSpinBox = this->get_node<Node>("UI/MenuPanel/TabContainer/Parameters/TabContainer/Cell/ScrollContainer/VBoxContainer/ResourceProportionContainer/SpinBox");
	ResourceProportionSpinBox->connect("value_changed", Callable(this, "setResourceProportion"));

	// Spawn back ground cells that don't die
	for (int i = 0; i < this->getNumCells(); i++) {
		this->spawnCell(1);
	}

	// Spawn nutrient zones
	CellEnvironment *environment = this->get_node<CellEnvironment>("CellEnvironment");
	for (int i = 0; i < environment->getNNutrientZones(); i++) {
		environment->spawnNutrientZone();
	}
}