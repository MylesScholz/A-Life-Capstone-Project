#pragma once

#include "cell_environment.hpp"
#include "cell_spawner.hpp"
#include "lineage_camera.hpp"
#include "stats.hpp"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/engine.hpp>

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