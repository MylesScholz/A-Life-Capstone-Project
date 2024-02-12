#include "cell_spawner.hpp"
#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void CellSpawner::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_num_cells"), &CellSpawner::getNumCells);
	ClassDB::bind_method(D_METHOD("set_num_cells", "num_cells"),
			&CellSpawner::setNumCells);
	ClassDB::add_property("CellSpawner", PropertyInfo(Variant::INT, "num_cells"),
			"set_num_cells", "get_num_cells");

	ClassDB::bind_method(D_METHOD("get_cell_scene"), &CellSpawner::getCellScene);
	ClassDB::bind_method(D_METHOD("set_cell_scene", "cell_scene"),
			&CellSpawner::setCellScene);
	ClassDB::add_property("CellSpawner",
			PropertyInfo(Variant::OBJECT, "cell_scene"),
			"set_cell_scene", "get_cell_scene");

	ClassDB::bind_method(D_METHOD("get_min_force"), &CellSpawner::getMinForce);
	ClassDB::bind_method(D_METHOD("set_min_force", "min_force"),
			&CellSpawner::setMinForce);
	ClassDB::add_property("CellSpawner", PropertyInfo(Variant::INT, "min_force"),
			"set_min_force", "get_min_force");

	ClassDB::bind_method(D_METHOD("get_max_force"), &CellSpawner::getMaxForce);
	ClassDB::bind_method(D_METHOD("set_max_force", "max_force"),
			&CellSpawner::setMaxForce);
	ClassDB::add_property("CellSpawner", PropertyInfo(Variant::INT, "max_force"),
			"set_max_force", "get_max_force");
}

CellSpawner::CellSpawner() { rand.instantiate(); }
CellSpawner::~CellSpawner() {}

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
	// Instantiate cell scene
	Node *cell = _cellScene->instantiate();
	// Get viewport size for positioning
	Size2 viewportSize = get_viewport()->get_visible_rect().size;
	// Cast cell scene to Cell object for ease of use
	Cell *cellObject = Object::cast_to<Cell>(cell);

	// Set Cell size
	cellObject->applyScale(rand->randf_range(0.25, 1));
	Size2 cellSize = cellObject->getSpriteSize();

	// Set Cell position to random location in viewport
	cellObject->set_position(Vector2(
			rand->randi_range(cellSize.x / 4, viewportSize.x - cellSize.x / 4),
			rand->randi_range(cellSize.y / 4, viewportSize.y - cellSize.y / 4)));

	// Apply random initial force to Cell
	float force_magnitude = rand->randf_range(_minForce, _maxForce);
	float direction = rand->randf_range(0, 2 * Math_PI);
	Vector2 force = Vector2(0, -1).rotated(direction) * force_magnitude;
	cellObject->apply_force(force);

	// Set z-index to ensure it's rendered behind other nodes
	cellObject->set_z_index(-1);

	// Prevent display cells from dying
	cellObject->setImmortal(isImmortal);

	add_child(cell);
}

void CellSpawner::removeAllCells() {
	for (int i = get_child_count() - 1; i >= 0; i--) {
		Node *child = get_child(i);
		if (Object::cast_to<Cell>(child)) {
			Object::cast_to<Cell>(child)->resetCollisions();
			child->queue_free();
		}
	}
}

void CellSpawner::_ready() {
	// Don't run if in editor
	if (Engine::get_singleton()->is_editor_hint())
		return;
	// Spawn back ground cells that don't die
	for (int i = 0; i < this->getNumCells(); i++) {
		this->spawnCell(1);
	}
}