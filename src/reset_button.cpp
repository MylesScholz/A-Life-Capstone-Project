#include "reset_button.hpp"
#include "cell_spawner.hpp"
#include "time_counter.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void ResetButton::_bind_methods() {}

ResetButton::ResetButton() {}
ResetButton::~ResetButton() {}

// _pressed is used as the function for when the button is pressed
void ResetButton::_pressed() {
	// Clear Cell selection
	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));
	Stats *stats = spawner->get_node<Stats>("UI/StatsPanel/TabContainer/Stats");
	stats->_clear_selected_cell();

	Camera2D *ui_cam = spawner->get_node<Camera2D>("UI_Cam");
	ui_cam->call("clear_selection");

	// Remove old Cells
	spawner->removeAllCells();

	// Respawn new Cells
	Object::cast_to<TimeCounter>(spawner->get_child(1))->reset_time();
	for (int i = 0; i < spawner->getNumCells(); i++) {
		spawner->spawnCell();
	}

	// Respawn NutrientZones
	CellEnvironment *environment = spawner->get_node<CellEnvironment>("CellEnvironment");
	environment->removeAllNutrientZones();
	for (int i = 0; i < environment->getNNutrientZones(); i++) {
		environment->spawnNutrientZone();
	}
}