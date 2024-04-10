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
	Object::cast_to<CanvasItem>(UI->find_child("BarPanel"))->set_visible(false); // Menu
	Object::cast_to<CanvasItem>(UI->find_child("NavBar"))->set_visible(true); // NavBar
	Object::cast_to<CanvasItem>(UI->find_child("StatsPanel"))->set_visible(true); // Stats
	Object::cast_to<FpsCounter>(UI->find_child("FpsCounter"))->toggle_fps();
	Object::cast_to<TimeCounter>(UI->find_child("TimeCounter"))->toggle_time();

	for (int i = 0; i < spawner->getNumCells(); i++) {
		spawner->spawnCell();
	}
}