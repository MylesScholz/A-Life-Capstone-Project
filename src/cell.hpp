#pragma once
#include "cell_state.hpp"
#include "cell_structure.hpp"
#include "genome.hpp"
#include "mitochondria.hpp"
#include "nucleus.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
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

	void keepCellsInBackground();

	void applyScale(const float);
	float getScale() const;

	float incrementNutrients(const float);

	Size2 getSpriteSize() const;

	void resetCollisions();

	void setImmortal(bool);

	void _ready() override;
	void _process(double) override;
	void _on_body_entered(Node *body);

	void _input_event(Node *viewport, Ref<InputEvent> event, int shape_idx);
	Array getStats() const;

private:
	CellState *_cellState;
	Size2 _spriteSize;
	Vector<CellStructure *> _cellStructures;
	Genome _cellGenome;

	Ref<RandomNumberGenerator> _rand;
};