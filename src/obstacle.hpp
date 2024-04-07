#pragma once

#include <godot_cpp/classes/static_body2d.hpp>

using namespace godot;

class Obstacle : public StaticBody2D {
	GDCLASS(Obstacle, StaticBody2D)

protected:
	static void _bind_methods();

public:
	Obstacle();
	~Obstacle();

private:
};