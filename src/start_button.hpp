#pragma once

#include "cell_spawner.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/button.hpp>

namespace godot {

class StartButton : public Button {
	GDCLASS(StartButton, Button)

protected:
	static void _bind_methods();

public:
	StartButton();
	~StartButton();

	void _ready() override;

	void _pressed() override;
};

} //namespace godot