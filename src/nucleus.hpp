#pragma once

#include "cell_structure.hpp"

using namespace godot;

class Nucleus : public CellStructure {
	GDCLASS(Nucleus, CellStructure)

protected:
	static void _bind_methods();

public:
	Nucleus();
	~Nucleus();

	void activate(CellState *) override;
	void modify(String, float) override;

	void setReproductionNutrientThreshold(const float);
	float getReproductionNutrientThreshold() const;

	void setReproductionEnergyThreshold(const float);
	float getReproductionEnergyThreshold() const;
	void increaseProtectingCount(const float);
	int getProtectingCount() const;

	void addMutationChance(const float);
	int getMutationCount() const;
	int getMutationChance(const int);

	void _ready() override;

private:
	float _reproductionNutrientThreshold;
	float _reproductionEnergyThreshold;
	int _protectingCount;
	bool _hasUpdatedState;
	Vector<float> _mutationChances;
};
