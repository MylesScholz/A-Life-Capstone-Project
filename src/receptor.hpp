#pragma once

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Receptor : public Area2D {
	GDCLASS(Receptor, Area2D)

protected:
	static void _bind_methods();

public:
	Receptor();
	~Receptor();

	void _on_area_entered(Area2D *);
	void _on_area_exited(Area2D *);

	void setScale(const float);

	void setSprite(AnimatedSprite2D *);
	AnimatedSprite2D *getSprite();

	void _ready() override;

private:
	float _baseSpriteScale;
	AnimatedSprite2D *_sprite;
};