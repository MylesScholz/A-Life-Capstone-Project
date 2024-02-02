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

	Button *exitMenuButton = spawner->get_node<Button>("UI/MenuPanel/EXIT_TO_MENUButton");

	// call through to exitMenuButton to reset the UI
	exitMenuButton->call("ui_reset");
}