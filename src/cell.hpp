#pragma once
#include "cell_state.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/rigid_body2D.hpp>

namespace godot {

class Cell : public RigidBody2D {
	GDCLASS(Cell, RigidBody2D)

protected:
	static void _bind_methods();

public:
	static int CollisionCount;

	Cell();
	~Cell();

	void applyScale(float);

	float getScale() const;
	Size2 getSpriteSize() const;

	void _ready() override;
	void _process(double) override;
	void _on_body_entered(Node *body);

private:
	CellState *_cellState;
	Size2 _spriteSize;
	Ref<RandomNumberGenerator> rand;
};

} // namespace godot