#include "start_button.hpp"
#include "fps_counter.hpp"
#include "time_counter.hpp"

#include <godot_cpp/core/class_db.hpp>

#include "helpers.hpp"

void StartButton::_bind_methods() {
}

StartButton::StartButton() {
}

StartButton::~StartButton() {
}

// _pressed is used as the function for when the button is pressed
//  This button is also switching the button off once it gets pressed once.
void StartButton::_pressed() {
	// Hide the menu and all of it's components
	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));
	spawner->removeAllCells();

	// Show in-simulation display
	Node *UI = spawner->get_child(1);
	Object::cast_to<CanvasItem>(UI->get_child(4))->set_visible(false); // Menu
	Object::cast_to<CanvasItem>(UI->get_child(5))->set_visible(true); // NavBar
	Object::cast_to<CanvasItem>(UI->get_child(2))->set_visible(true); // Stats
	Object::cast_to<FpsCounter>(UI->find_child("FpsCounter"))->toggle_fps();
	Object::cast_to<TimeCounter>(UI->find_child("TimeCounter"))->toggle_time();

	for (int i = 0; i < spawner->getNumCells(); i++) {
		UtilityFunctions::print("Starting");
		spawner->spawnCell();
	}

	CellEnvironment *environment = spawner->get_node<CellEnvironment>("CellEnvironment");
	environment->removeAllNutrientZones();
	for (int i = 0; i < environment->getNNutrientZones(); i++) {
		environment->spawnNutrientZone();
	}
}