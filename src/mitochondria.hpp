#pragma once

#include "cell_structure.hpp"

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Mitochondria : public CellStructure {
	GDCLASS(Mitochondria, CellStructure);

protected:
	static void _bind_methods();

public:
	Mitochondria();
	~Mitochondria();

	void activate(CellState *) override;
};
