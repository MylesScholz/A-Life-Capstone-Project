#pragma once

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Receptor : public Area2D {
	GDCLASS(Receptor, Area2D)

protected:
	static void _bind_methods();

public:
	Receptor();
	~Receptor();

	void _on_body_entered(Node *);
	void _on_body_exited(Node *);

	void setSprite(Sprite2D *);
	Sprite2D *getSprite();

	void _ready() override;

private:
	Sprite2D *_sprite;
};