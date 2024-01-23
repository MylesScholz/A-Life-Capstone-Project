#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot {

class CellState : public Node {
	GDCLASS(CellState, Node)

protected:
	static void _bind_methods();

public:
	CellState();
	~CellState();

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

	void setMovementForce(const Vector2 &force);
	Vector2 getMovementForce() const;

private:
	bool _alive;
	float _age;
	float _lifespan;
	float _scale;
	Ref<Flagella> _flagella;
};

class Flagella : public Node {
	GDCLASS(Flagella, Node);

protected:
	static void _bind_methods():

public:
	Flagella():
	~Flagella():

	void setMovementForce(const Vector2 &force);
	Vector2 getMovementForce() const;

private:
	Vector2 _movement_force;

};

}; // namespace godot