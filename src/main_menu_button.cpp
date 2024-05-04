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
	// Remove old nutrient zones
	CellEnvironment *environment = spawner->get_node<CellEnvironment>("CellEnvironment");
	environment->removeAllNutrientZones();

	// Close in-simulation display
	Node *UI = spawner->get_node<Node>("UI");
	UI->get_node<CanvasItem>("NavBar")->set_visible(false);
	UI->get_node<CanvasItem>("StatsPanel")->set_visible(false);
	UI->get_node<CanvasItem>("MenuPanels/SaveAndQuitMenuPanel")->set_visible(false);
	Object::cast_to<FpsCounter>(UI->find_child("FpsCounter"))->toggle_fps();
	Object::cast_to<TimeCounter>(UI->find_child("TimeCounter"))->toggle_time();
	Object::cast_to<Label>(UI->find_child("SpeedDisplay"))->call("toggle_display");

	UI->get_node<CanvasItem>("BarPanel")->set_visible(true); // Open menu

	// Respawn background cells that don't die
	spawner->get_node<Node>("UI/NavBar/PauseButton")->call("unpause");
	for (int i = 0; i < spawner->getNumCells(); i++) {
		spawner->spawnCell(1);
	}
}