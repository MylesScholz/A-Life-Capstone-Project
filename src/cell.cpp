#include "cell.hpp"
#include "cell_environment.hpp"
#include "cell_membrane.hpp"
#include "flagella.hpp"
#include "mitochondria.hpp"
#include "nucleus.hpp"
#include "ribosomes.hpp"

#include "cell_membrane_gene.hpp"
#include "flagella_gene.hpp"
#include "mitochondria_gene.hpp"
#include "modifier_gene.hpp"
#include "nucleus_gene.hpp"
#include "ribosomes_gene.hpp"

#include "cell_spawner.hpp"
#include "stats_counter.hpp"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/os.hpp>

#include "helpers.hpp"
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void Cell::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &Cell::_on_body_entered);

	ClassDB::bind_method(D_METHOD("getStats"), &Cell::getStats);

	ADD_SIGNAL(MethodInfo("cell_selected", PropertyInfo(Variant::OBJECT, "cell")));

	ClassDB::bind_method(D_METHOD("_on_cell_growth"), &Cell::_on_cell_growth);
	ADD_SIGNAL(MethodInfo("cell_growth"));

	ADD_SIGNAL(MethodInfo("cell_death"));
}

int Cell::CollisionCount = 0;
bool immortal = 0;

void Cell::seteq(Cell *otherCell) {
	// Create new genome. Overwriting the existing one should destruct it
	_cellGenome = Genome();

	// Copy genome of otherCell
	for (int i = 0; i < otherCell->_cellGenome.getSize(); ++i) {
		Gene *gene = otherCell->_cellGenome.getGene(i);

		Gene *newGene = gene->clone();
		_cellGenome.addGene(newGene);
	}

	// Copy relevant cell state information
	_cellState = this->get_node<CellState>("CellState");
	_cellState->setAlive(otherCell->_cellState->getAlive());
	_cellState->setLifespan(otherCell->_cellState->getLifespan());
	_cellState->setHomeostasisNutrientCost(otherCell->_cellState->getHomeostasisNutrientCost());
	_cellState->setReproductionNutrientCost(otherCell->_cellState->getReproductionNutrientCost());
	_cellState->setTotalNutrients(otherCell->_cellState->getTotalNutrients());
	_cellState->setNutrientMaximum(otherCell->_cellState->getNutrientMaximum());
	_cellState->setHomeostasisEnergyCost(otherCell->_cellState->getHomeostasisEnergyCost());
	_cellState->setReproductionEnergyCost(otherCell->_cellState->getReproductionEnergyCost());
	_cellState->setTotalEnergy(otherCell->_cellState->getTotalEnergy());
	_cellState->setEnergyMaximum(otherCell->_cellState->getEnergyMaximum());

	float halfArea = (sqrt(2) / 2);
	otherCell->applyScale(halfArea);
	applyScale(otherCell->_cellState->getScale());

	// Not sure if this makes sense to do
	_spriteSize = otherCell->getSpriteSize();
}

Cell::Cell() {
	// Setting default required parameters for collision detection on RigidBody2D
	// objects, then applying the signal to Cell objects.
	this->set_contact_monitor(true);
	this->set_max_contacts_reported(
			1000); // Adjust max contacts as complexity increases.
	this->connect("body_entered", Callable(this, "_on_body_entered"));

	// Instantiate the random number generator
	_rand.instantiate();

	// Temporary genome for start screen
	_cellGenome.addGene(new NucleusGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(new MitochondriaGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(new RibosomesGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(new CellMembraneGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(new FlagellaGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
	_cellGenome.addGene(randomModifierGene());
}
Cell::~Cell() {
	queue_free();
}

void Cell::activateCellStructures() {
	for (auto &structure : _cellStructures) {
		if (structure) {
			structure->activate(_cellState);
		}
	}
}

void Cell::keepCellsInBackground() {
	for (auto &structure : _cellStructures) {
		if (structure) {
			this->set_z_index(-2);
			if (structure->get_class() == "Flagella")
				structure->set_z_index(-1);
			else
				structure->set_z_index(0);
		}
	}
}

void Cell::applyScale(const float scale) {
	if (scale <= 0)
		return;

	_cellState = this->get_node<CellState>("CellState");
	if (_cellState && _cellState->getScale() * scale > 1)
		return;

	// Apply the scaling to the collision shape, sprite, and CellState
	this->get_node<CollisionShape2D>("CollisionShape2D")->apply_scale(Vector2(scale, scale));
	_cellState->applyScale(scale);

	// Apply scaling to nutrient and energy maxima; capacity is analogous to area for a circle,
	// so the area scaling ratio is the linear scaling ratio (s) squared:
	// A2 / A1
	// (pi * r2 ^ 2) / (pi * r1 ^ 2)
	// r2 = s * r1
	// (s ^ 2 * r1 ^ 2) / (r1 ^ 2)
	// s ^ 2
	float newNutrientMaximum = _cellState->getNutrientMaximum() * scale * scale;
	_cellState->setNutrientMaximum(newNutrientMaximum);

	float newEnergyMaximum = _cellState->getEnergyMaximum() * scale * scale;
	_cellState->setEnergyMaximum(newEnergyMaximum);

	// Apply scaling to mass; scale is squared because mass is proportional to area for a circle
	this->set_mass(this->get_mass() * scale * scale);

	// Apply scaling to each CellStructure
	for (auto &structure : _cellStructures) {
		if (structure)
			structure->applyScale(scale);
	}
}
float Cell::getScale() const { return this->get_node<CellState>("CellState")->getScale(); }

float Cell::incrementNutrients(const float nutrients) {
	// The actual nutrient increment may be less than the parameter value due to boundaries
	float actualIncrement = 0;

	if (_cellState->getTotalNutrients() + nutrients < 0) {
		actualIncrement = -_cellState->getTotalNutrients();
	} else if (_cellState->getTotalNutrients() + nutrients > _cellState->getNutrientMaximum()) {
		actualIncrement = _cellState->getNutrientMaximum() - _cellState->getTotalNutrients();
	} else {
		actualIncrement = nutrients;
	}
	_cellState->incrementTotalNutrients(actualIncrement);

	// Return the actual amount of nutrients incremented
	return actualIncrement;
}

Size2 Cell::getSpriteSize() const { return _spriteSize; }

void Cell::resetCollisions() {
	CollisionCount = 0;
	return;
}

void Cell::setImmortal(bool isImmortal) {
	immortal = isImmortal;
	return;
}

void Cell::_ready() {
	// Add CellStructures using the cell genome
	_cellStructures = _cellGenome.expressGenes();
	for (auto &structure : _cellStructures) {
		this->add_child(structure);

		if (structure->getScale() != _cellState->getScale())
			structure->applyScale(_cellState->getScale() / structure->getScale());
	}

	this->set_pickable(true);
	_cellState = this->get_node<CellState>("CellState");

	float sumReproductionNutrientCost = 0;
	float sumReproductionEnergyCost = 0;

	for (CellStructure *structure : _cellStructures) {
		sumReproductionNutrientCost += structure->getCreationNutrientCost();
		sumReproductionEnergyCost += structure->getCreationEnergyCost();
	}

	_cellState->setReproductionNutrientCost(sumReproductionNutrientCost);
	_cellState->setReproductionEnergyCost(sumReproductionEnergyCost);

	CellMembrane *cellMembrane = this->get_node<CellMembrane>("CellMembrane");
	if (cellMembrane) {
		_spriteSize = cellMembrane->getSpriteSize();
		cellMembrane->connect("cell_growth", Callable(this, "_on_cell_growth"));
	}
}

void Cell::_process(double delta) {
	DONT_RUN_IN_EDITOR;

	this->keepCellsInBackground();
	if (_cellState->getAlive()) {
		// Living Cell behavior

		// Activate the Cell's structures
		this->activateCellStructures();

		// Apply Flagella Movement Vectors
		this->apply_force(_cellState->getNextMovementVector().rotated(this->get_rotation()));

		// Decrement the Cell's nutrients
		_cellState->incrementTotalNutrients(-delta * _cellState->getHomeostasisNutrientCost());
		// Decrement the Cell's energy
		_cellState->incrementTotalEnergy(-delta * _cellState->getHomeostasisEnergyCost());

		// Aging, starvation and death
		float nutrients = 100.0;
		float ageDiff = 0;
		float energy = 100.0;
		if (!immortal) {
			nutrients = _cellState->getTotalNutrients();
			_cellState->increaseAge(delta);
			ageDiff = _cellState->getAge() - _cellState->getLifespan();
			energy = _cellState->getTotalEnergy();
		}
		if (ageDiff > 0) {
			// The Cell's age exceeds its lifespan

			// Generate a random number from 0 to the Cell's lifespan times 1 over
			// delta. If that value is less than ageDiff, kill the Cell. This adds
			// some variability to Cell lifespans.
			if (_rand->randf_range(0, (1.0 / delta) * _cellState->getLifespan()) < ageDiff) {
				_cellState->setAlive(false);
				// Stop Cell movement
				this->set_linear_damp(10.0);
				this->set_angular_damp(10.0);
				// Create NutrientZone
				this->emit_signal("cell_death", this);
				// Remove the Cell from the scene
				queue_free();
			}
		}
		if (nutrients <= 0 || energy <= 0) {
			_cellState->setAlive(false);
			// Stop Cell movement
			this->set_linear_damp(10.0);
			this->set_angular_damp(10.0);
			// Create NutrientZone
			this->emit_signal("cell_death", this);
			// Remove the Cell from the scene
			queue_free();
		}
	}
}

void Cell::_input_event(Node *viewport, Ref<InputEvent> event, int shape_idx) {
	Ref<InputEventMouseButton> mouse_button_event = event;
	if (mouse_button_event.is_valid() && mouse_button_event->is_pressed() && mouse_button_event->get_button_index() == MOUSE_BUTTON_LEFT) {
		UtilityFunctions::print("press detected");
		UtilityFunctions::print(this);

		//Object* stats_container = ResourceLoader::get_singleton()->load("res://StatsContainer.gd");
		//Node *global_signals = Object::cast_to<Node>(Engine::get_singleton()->get_singleton("res://GlobalSignals.gd"));

		CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));
		StatsCounter *statsCounter = spawner->get_node<StatsCounter>("UI/StatsPanel/StatsCounter");

		emit_signal("cell_selected", this);

		statsCounter->_update_Stats(this);
		//statsCounter->_update_signal(this);
	}
}

Array Cell::getStats() const {
	Array stats;
	stats.push_back(Math::round(_cellState->getBirthTime() * 1000.0) / 1000.0); // index 0
	stats.push_back(_cellState->getAlive()); // index 1
	stats.push_back(Math::round(_cellState->getAge() * 1000.0) / 1000.0);
	stats.push_back(Math::round(_cellState->getTotalEnergy() * 1000.0) / 1000.0);
	stats.push_back(Math::round(_cellState->getEnergyMaximum() * 1000.0) / 1000.0);
	stats.push_back(Math::round(_cellState->getTotalNutrients() * 1000.0) / 1000.0);
	stats.push_back(Math::round(_cellState->getNutrientMaximum() * 1000.0) / 1000.0);
	stats.push_back(Math::round(get_mass() * 1000000) / 1000000.00);
	stats.push_back(Math::round(_cellState->getScale() * 1000000) / 1000000.00);
	// Continue adding stats in a specific order
	return stats;
}

// function updates on cell contacts. Increments counter for use in
// stats_counter.cpp
void Cell::_on_body_entered(Node *body) { CollisionCount++; }

void Cell::_on_cell_growth() {
	// Area (a)  is used for calculating the cost of growth
	// a = pi * r^2
	float area = Math_PI * _cellState->getScale() * _cellState->getScale();

	// deltaArea (dA) is used for calculating the cost of growth
	// dA = A - a
	// dA = (pi * R^2) - (pi * r^2)
	// dA = pi * (R^2 - r^2)
	// R = s * r where s = _cellState->getGrowthRate()
	// dA = pi * (s^2 * r^2 - r^2)
	// dA = pi * r^2 * (s^2 - 1)
	// dA = a * (s^2 - 1)
	float deltaArea = area * (_cellState->getGrowthRate() * _cellState->getGrowthRate() - 1);

	// Calculate the cost of growth in nutrients and energy
	float growthNutrientCost = _cellState->getGrowthNutrientCost() * deltaArea;
	float growthEnergyCost = _cellState->getGrowthEnergyCost() * deltaArea;

	// Check that the Cell has sufficient nutrients and energy to grow
	if (_cellState->getTotalNutrients() >= growthNutrientCost && _cellState->getTotalEnergy() >= growthEnergyCost) {
		// Deduct the growth cost from the Cell
		_cellState->incrementTotalNutrients(-growthNutrientCost);
		_cellState->incrementTotalEnergy(-growthEnergyCost);

		// Grow the Cell
		applyScale(_cellState->getGrowthRate());

		CellMembrane *cellMembrane = this->get_node<CellMembrane>("CellMembrane");
		cellMembrane->getSprite()->set_frame(1);
		cellMembrane->getSprite()->play("activate");
	}
}