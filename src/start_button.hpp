#pragma once

#include "cell_spawner.hpp"
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

class StartButton : public Button {
	GDCLASS(StartButton, Button)

protected:
	static void _bind_methods();

public:
	StartButton();
	~StartButton();

	void _pressed() override;
};