#include "main_menu_button.hpp"
#include "cell_spawner.hpp"
#include "fps_counter.hpp"
#include "time_counter.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void MainMenuButton::_bind_methods() {}

MainMenuButton::MainMenuButton() {}
MainMenuButton::~MainMenuButton() {}

// _pressed is used as the function for when the button is pressed
void MainMenuButton::_pressed() {
	// Remove old cells
	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));
	spawner->removeAllCells();

	// Close in-simulation display
	Node *UI = spawner->get_child(1);
	Object::cast_to<CanvasItem>(UI->get_child(5))->set_visible(false); // NavBar
	Object::cast_to<CanvasItem>(UI->get_child(2))->set_visible(false); // Stats
	Object::cast_to<FpsCounter>(UI->find_child("FpsCounter"))->toggle_fps();
	Object::cast_to<TimeCounter>(UI->find_child("TimeCounter"))->toggle_time();

	Object::cast_to<CanvasItem>(UI->get_child(4))->set_visible(true); // Open menu

	// Respawn background cells that don't die
	for (int i = 0; i < spawner->getNumCells(); i++) {
		spawner->spawnCell(1);
	}
}