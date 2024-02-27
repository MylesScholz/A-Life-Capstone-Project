#include "cell.hpp"
#include "flagella.hpp"
#include "mitochondria.hpp"
#include "nucleus.hpp"
#include "ribosomes.hpp"

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>

void Cell::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &Cell::_on_body_entered);
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

	// Add CellStructures

	// Load a CellStructure scene
	Ref<PackedScene> nucleus_scene = ResourceLoader::get_singleton()->load("res://nucleus.tscn");
	// Instantiate the scene and cast it to the specific type
	Nucleus *nucleus = Object::cast_to<Nucleus>(nucleus_scene->instantiate());
	// Add the CellStructure pointer to _cellStructures and as a child under this Cell
	_cellStructures.push_back(nucleus);
	this->add_child(nucleus);

	Ref<PackedScene> mitochondria_scene = ResourceLoader::get_singleton()->load("res://mitochondria.tscn");
	Mitochondria *mitochondria = Object::cast_to<Mitochondria>(mitochondria_scene->instantiate());
	_cellStructures.push_back(mitochondria);
	this->add_child(mitochondria);

	Ref<PackedScene> ribosomes_scene = ResourceLoader::get_singleton()->load("res://ribosomes.tscn");
	Ribosomes *ribosomes = Object::cast_to<Ribosomes>(ribosomes_scene->instantiate());
	_cellStructures.push_back(ribosomes);
	this->add_child(ribosomes);

	Ref<PackedScene> flagella_scene = ResourceLoader::get_singleton()->load("res://flagella.tscn");
	Flagella *flagella = Object::cast_to<Flagella>(flagella_scene->instantiate());
	_cellStructures.push_back(flagella);
	this->add_child(flagella);

	_spriteSize = Size2();
}
Cell::~Cell() {
	queue_free();
}

void Cell::activateCellStructures() {
	for (auto &structure : _cellStructures) {
		if (structure)
			structure->activate(_cellState);
	}
}

void Cell::applyScale(const float scale) {
	if (scale <= 0)
		return;

	// Apply the scaling to the collision shape, sprite, and CellState
	this->get_node<CollisionShape2D>("CollisionShape2D")->apply_scale(Vector2(scale, scale));
	this->get_node<Sprite2D>("Sprite")->apply_scale(Vector2(scale, scale));
	this->get_node<CellState>("CellState")->applyScale(scale);

	// Apply scaling to mass; scale is squared because mass is proportional to area
	this->set_mass(this->get_mass() * scale * scale);

	// Apply scaling to each CellStructure
	for (auto &structure : _cellStructures) {
		if (structure)
			structure->applyScale(scale);
	}

	// Measure the new sprite size
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

		// Activate the Cell's structures
		this->activateCellStructures();

		// Apply Flagella Movement Vectors
		this->apply_force(_cellState->getNextMovementVector());

		// Decrement the Cell's nutrients
		_cellState->incrementTotalNutrients(-delta * _cellState->getHomeostasisNutrientCost());
		// Decrement the Cell's energy
		_cellState->incrementTotalEnergy(-delta * _cellState->getHomeostasisEnergyCost());

		// Aging, starvation, and death
		float nutrients = _cellState->getTotalNutrients();
		float energy = _cellState->getTotalEnergy();
		float ageDiff = _cellState->getAge(Time::get_singleton()->get_ticks_msec()) - _cellState->getLifespan();
		if (ageDiff > 0) {
			// The Cell's age exceeds its lifespan

			// Generate a random number from 0 to the Cell's lifespan times 1 over
			// delta. If that value is less than ageDiff, kill the Cell. This adds
			// some variability to Cell lifespans.
			if (rand->randf_range(0, (1.0 / delta) * _cellState->getLifespan()) < ageDiff) {
				_cellState->setAlive(false);
				// Stop Cell movement
				this->set_linear_damp(10.0);
				this->set_angular_damp(10.0);
			}
		}
		if (nutrients <= 0 || energy <= 0) {
			_cellState->setAlive(false);
			// Stop Cell movement
			this->set_linear_damp(10.0);
			this->set_angular_damp(10.0);
		}
	}
}

// function updates on cell contacts. Increments counter for use in
// stats_counter.cpp
void Cell::_on_body_entered(Node *body) { CollisionCount++; }
