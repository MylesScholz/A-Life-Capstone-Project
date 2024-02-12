#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot {

class Mitochondria : public Node {
	GDCLASS(Mitochondria, Node);

protected:
	static void _bind_methods();

public:
	Mitochondria();
	~Mitochondria();
};

}; // namespace godot