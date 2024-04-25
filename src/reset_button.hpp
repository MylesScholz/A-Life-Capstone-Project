#pragma once

#include "cell_spawner.hpp"
#include "stats.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/button.hpp>

namespace godot {

class ResetButton : public Button {
	GDCLASS(ResetButton, Button)

protected:
	static void _bind_methods();

public:
	ResetButton();
	~ResetButton();

	void _pressed();
};

} //namespace godot