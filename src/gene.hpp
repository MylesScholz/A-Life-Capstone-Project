#pragma once

#include "cell_structure.hpp"
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Gene : public Node {
	GDCLASS(Gene, Node)

protected:
	static void _bind_methods();

public:
	Gene(/* args */);
	~Gene();

	virtual String getType();
	virtual String getName();
	virtual CellStructure *express();
	virtual float getValue();

private:
	/* data */
};