#include "start_button.hpp"

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
	CellSpawner *parent = static_cast<CellSpawner *>(this->get_parent());
	for (int i = 0; i < parent->getNumCells(); i++) {
		parent->spawnCell();
	}
	this->set_visible(false);
}

// Mainly used for setting diffrent values for the button but these could be done in the godot client instead
//
void StartButton::_ready() {
	DONT_RUN_IN_EDITOR;

	this->set_text("Start");
}