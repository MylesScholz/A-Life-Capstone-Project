#pragma once

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

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

	void setSprite(Sprite2D *);
	Sprite2D *getSprite();

	void _ready() override;

private:
	float _baseSpriteScale;
	Sprite2D *_sprite;
};