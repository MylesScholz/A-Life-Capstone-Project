#pragma once

#include "cell_environment.hpp"
#include "cell_spawner.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/texture_button.hpp>

namespace godot {

class ResetButton : public TextureButton {
	GDCLASS(ResetButton, TextureButton)

protected:
	static void _bind_methods();

public:
	ResetButton();
	~ResetButton();

	void _pressed();
};

} //namespace godot