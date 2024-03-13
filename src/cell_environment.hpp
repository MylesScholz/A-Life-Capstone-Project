#pragma once

#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

class CellEnvironment : public Area2D {
	GDCLASS(CellEnvironment, Area2D)

protected:
	static void _bind_methods();

public:
	CellEnvironment();
	~CellEnvironment();

	/* Methods */

private:
	/* Attributes */
};