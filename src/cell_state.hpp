#pragma once

#include "mitochondria.hpp"
#include "nucleus.hpp"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class CellState : public Node {
	GDCLASS(CellState, Node)

protected:
	static void _bind_methods();

public:
	CellState();
	~CellState();

	void setMitochondria(Mitochondria *);
	Mitochondria *getMitochondria();

	void setAlive(const bool);
	bool getAlive() const;

	void setAge(const float);
	void incrementAge(const float);
	float getAge() const;

	void setLifespan(const float);
	float getLifespan() const;

	void setNucleus(Nucleus *);
	Nucleus *getNucleus() const;

	void setScale(const float);
	void applyScale(const float);
	float getScale() const;

	void _ready() override;
	void setMovementForce(const Vector2 &force);
	Vector2 getMovementForce() const;

private:
	Nucleus *_nucleus;
	Mitochondria *_mitochondria;
	Flagella *_flagella;
	float _age;
	float _scale;
};

}; // namespace godot