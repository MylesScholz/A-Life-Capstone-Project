#include "cell_spawner.hpp"
#include "cell.hpp"
#include "cell_environment.hpp"
#include "stats_counter.hpp"

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

	ClassDB::bind_method(D_METHOD("_on_cell_reproduction", "cell"), &CellSpawner::_on_cell_reproduction);
	ADD_SIGNAL(MethodInfo("cell_reproduction", PropertyInfo(Variant::OBJECT, "cell")));

	ADD_SIGNAL(MethodInfo("cell_selected", PropertyInfo(Variant::OBJECT, "cell")));
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

void CellSpawner::spawnCell(bool isImmortal) {
	// Create a RandomNumberGenerator object
	RandomNumberGenerator rand = RandomNumberGenerator();

	// Instantiate cell scene
	Node *cell = _cellScene->instantiate();
	// Get viewport size for positioning
	Size2 viewportSize = get_viewport()->get_visible_rect().size;
	// Cast cell scene to Cell object for ease of use
	Cell *cellObject = Object::cast_to<Cell>(cell);

	// Set Cell size
	cellObject->applyScale(rand.randf_range(0.25, 1));
	Size2 cellSize = cellObject->getSpriteSize();

	// Set Cell position to random location in viewport
	cellObject->set_position(Vector2(
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

	CellEnvironment *cellEnvironment = this->get_node<CellEnvironment>("CellEnvironment");
	cellEnvironment->add_child(cell);
	cell->connect("cell_death", Callable(cellEnvironment, "_on_cell_death"));

	if (!isImmortal) // Do we want the cells on the title screen to be able to reproduce?
		cellObject->get_node<Nucleus>("Nucleus")->connect("cell_reproduction", Callable(this, "_on_cell_reproduction"));

	/*StatsCounter *statsCounter = this->get_node<StatsCounter>("UI/StatsPanel/StatsCounter");
	cellObject->connect("cell_selected", Callable(statsCounter, "_update_Stats"));*/
}

void CellSpawner::_on_cell_reproduction(Cell *cell) {
	// Create a RandomNumberGenerator object
	RandomNumberGenerator rand = RandomNumberGenerator();

	Node *childCell = _cellScene->instantiate();
	Cell *cellObject = Object::cast_to<Cell>(childCell);

	cellObject->seteq(cell);

	cellObject->set_position(cell->get_position());

	// This probably shouldn't be random for a child cell, and I assume w/ the flagella rework
	float force_magnitude = rand.randf_range(_minForce, _maxForce);
	float direction = rand.randf_range(0, 2 * Math_PI);
	Vector2 force = Vector2(0, -1).rotated(direction) * force_magnitude;
	cellObject->apply_force(force);

	cellObject->apply_torque(rand.randf_range(-500, 500));

	CellEnvironment *cellEnvironment = this->get_node<CellEnvironment>("CellEnvironment");
	cellEnvironment->add_child(childCell);
	childCell->connect("cell_death", Callable(cellEnvironment, "_on_cell_death"));

	cellObject->get_node<Nucleus>("Nucleus")->connect("cell_reproduction", Callable(this, "_on_cell_reproduction"));
}

void CellSpawner::removeAllCells() {
	CellEnvironment *env = this->get_node<CellEnvironment>("CellEnvironment");

	for (int i = env->get_child_count() - 1; i >= 0; i--) {
		Node *child = env->get_child(i);
		if (Object::cast_to<Cell>(child)) {
			Object::cast_to<Cell>(child)->resetCollisions();
			child->queue_free();
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

	// Spawn back ground cells that don't die
	for (int i = 0; i < this->getNumCells(); i++) {
		this->spawnCell(1);
	}
}