#pragma once

#include "mitochondria.hpp"
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

	void setScale(const float);
	void applyScale(const float);
	float getScale() const;

	void _ready() override;

private:
	Mitochondria *_mitochondria;
	bool _alive;
	float _age;
	float _lifespan;
	float _scale;
};

}; // namespace godot