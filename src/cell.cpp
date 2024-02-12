#include "cell.hpp"

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Cell::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_body_entered", "body"),
			&Cell::_on_body_entered);
}

int Cell::CollisionCount = 0;

Cell::Cell() {
	// Setting default required parameters for collision detection on RigidBody2D
	// objects, then applying the signal to Cell objects.
	this->set_contact_monitor(true);
	this->set_max_contacts_reported(
			1000); // Adjust max contacts as complexity increases.
	this->connect("body_entered", Callable(this, "_on_body_entered"));

	rand.instantiate();

	_spriteSize = Size2();
}
Cell::~Cell() {}

void Cell::applyScale(float scale) {
	if (scale <= 0)
		return;

	this->get_node<CollisionShape2D>("CollisionShape2D")
			->apply_scale(Vector2(scale, scale));
	this->get_node<Sprite2D>("Sprite")->apply_scale(Vector2(scale, scale));

	_cellState->applyScale(scale);
	_spriteSize = this->get_node<Sprite2D>("Sprite")->get_rect().size;
}

float Cell::getScale() const { return _cellState->getScale(); }

Size2 Cell::getSpriteSize() const { return _spriteSize; }

void Cell::_ready() {
	_cellState = this->get_node<CellState>("CellState");
}

void Cell::_process(double delta) {
	// Don't run if in editor
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (_cellState->getAlive()) {
		// Living Cell behavior

		// Increment the Cell's age and decrement nutrients
		_cellState->incrementTotalNutrients(-delta * _cellState->getHomeostasisNutrientCost());

		// Aging, starvation and death
		float nutrients = _cellState->getTotalNutrients();
		float ageDiff = _cellState->getAge(Time::get_singleton()->get_ticks_msec()) - _cellState->getLifespan();
		if (ageDiff > 0) {
			// The Cell's age exceeds its lifespan

			// Generate a random number from 0 to the Cell's lifespan times 1 over
			// delta. If that value is less than ageDiff, kill the Cell. This adds
			// some variability to Cell lifespans.
			if (rand->randf_range(0, (1.0 / delta) * _cellState->getLifespan()) <
					ageDiff) {
				_cellState->setAlive(false);
				// Stop Cell movement
				this->set_linear_damp(10.0);
			}
		}
		if (nutrients <= 0) {
			_cellState->setAlive(false);
			// Stop Cell movement
			this->set_linear_damp(10.0);
		}
	}
}

// function updates on cell contacts. Increments counter for use in
// stats_counter.cpp
void Cell::_on_body_entered(Node *body) { CollisionCount++; }
