#pragma once

#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

class Environment : public Area2D {
	GDCLASS(Environment, Area2D)

protected:
	static void _bind_methods();

public:
	Environment();
	~Environment();

	/* Methods */

private:
	/* Attributes */
};