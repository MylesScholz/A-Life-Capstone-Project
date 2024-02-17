#pragma once

#include "cell_structure.hpp"

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Flagella : public CellStructure {
	GDCLASS(Flagella, CellStructure)

protected:
	static void _bind_methods();

public:
	Flagella();
	~Flagella();

	void activate(CellState *) override;

	void setMovementForceVector(const Vector2 movementForceVector);
	Vector2 getMovementForceVector() const;

	void setPositionVector(const Vector2 positionVector);
	Vector2 getPositionVector() const;

	void setActivationEnergyCost(const float activationEnergyCost);
	float getActivationEnergyCost() const;

private:
	Vector2 _movementForceVector;
	Vector2 _positionVector;
	float _activationEnergyCost;
};
