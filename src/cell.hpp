#pragma once
#include "cell_state.hpp"
#include "cell_structure.hpp"
#include "genome.hpp"
#include "mitochondria.hpp"
#include "nucleus.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/templates/vector.hpp>

using namespace godot;

class Cell : public RigidBody2D {
	GDCLASS(Cell, RigidBody2D)

protected:
	static void _bind_methods();

public:
	static int CollisionCount;

	Cell();
	~Cell();

	void activateCellStructures();

	void applyScale(const float);
	float getScale() const;

	Size2 getSpriteSize() const;

	void _ready() override;
	void _process(double) override;
	void _on_body_entered(Node *body);

private:
	CellState *_cellState;
	Size2 _spriteSize;
	Vector<CellStructure *> _cellStructures;

	Ref<RandomNumberGenerator> rand;
	Genome cellGenome;
};