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
	// Remove old cells
	CellSpawner *spawner = (CellSpawner *)this->get_parent()->get_parent()->get_parent();
	spawner->removeAllCells();

	// Respawn new cells
	Object::cast_to<TimeCounter>(spawner->get_child(1))->reset_time();
	for (int i = 0; i < spawner->getNumCells(); i++) {
		spawner->spawnCell();
	}
}