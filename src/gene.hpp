#pragma once

#include "cell_structure.hpp"
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Gene {
public:
	Gene(/* args */);
	~Gene();

	virtual String getType();
	virtual String getName();
	virtual CellStructure *express();
	virtual float getValue();

	virtual Gene *clone() = 0;

private:
	/* data */
};