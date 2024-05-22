#pragma once

#include "cell_environment.hpp"
#include "cell_spawner.hpp"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/texture_button.hpp>

namespace godot {

class MainMenuButton : public TextureButton {
	GDCLASS(MainMenuButton, TextureButton)

protected:
	static void _bind_methods();

public:
	MainMenuButton();
	~MainMenuButton();

	// void _ready() override;

	void _pressed();
};

} //namespace godot