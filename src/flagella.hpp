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

	void setMovementForce(const Vector2 force);
	Vector2 getMovementForce() const;

private:
	Vector2 _movementForceVector;
	Vector2 _positionVector;
	float _activationEnergyCost;
};
