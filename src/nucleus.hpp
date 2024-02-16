#pragma once

#include "cell_structure.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Nucleus : public CellStructure {
	GDCLASS(Nucleus, CellStructure)

protected:
	static void _bind_methods();

public:
	Nucleus();
	~Nucleus();

	void activate(CellState *) override;

	void setReproductionNutrientThreshold(const float);
	float getReproductionNutrientThreshold() const;

private:
	float _reproductionNutrientThreshold;
};
