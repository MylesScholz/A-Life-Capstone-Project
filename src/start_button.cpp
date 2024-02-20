#include "start_button.hpp"
#include "fps_counter.hpp"
#include "time_counter.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

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
	CanvasItem *menu = Object::cast_to<CanvasItem>(this->get_parent());
	menu->set_visible(false);
	CellSpawner *spawner = (CellSpawner *)this->get_parent()->get_parent();
	spawner->removeAllCells();

	// Show in-simulation display
	Object::cast_to<CanvasItem>(spawner->get_child(5))->set_visible(true); // NavBar
	Object::cast_to<CanvasItem>(spawner->get_child(2))->set_visible(true); // Stats
	Object::cast_to<FpsCounter>(spawner->get_child(0))->toggle_fps();
	Object::cast_to<TimeCounter>(spawner->get_child(1))->toggle_time();

	for (int i = 0; i < spawner->getNumCells(); i++) {
		spawner->spawnCell();
	}
}