#pragma once

#include "cell_structure.hpp"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Flagella : public CellStructure {
	GDCLASS(Flagella, CellStructure)

protected:
	static void _bind_methods();

public:
	Flagella();
	~Flagella();

	void activate(CellState *) override;

	void setMovementForceVector(const Vector2);
	Vector2 getMovementForceVector() const;

	void setPositionVector(const Vector2);
	Vector2 getPositionVector() const;

	void setActivationEnergyCost(const float);
	float getActivationEnergyCost() const;

	void setActivationEnergyThreshold(const float);
	float getActivationEnergyThreshold() const;

	void _ready() override;

private:
	Vector2 _movementForceVector;
	Vector2 _positionVector;
	float _activationEnergyCost;
	float _activationEnergyThreshold;

	Ref<RandomNumberGenerator> rand;
};
