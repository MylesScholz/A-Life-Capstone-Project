#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot {

class Flagella : public Node {
	GDCLASS(Flagella, Node)

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