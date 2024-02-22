#pragma once


#include "cell_state.hpp"

using namespace godot;

class CellStructure : public Node {
	GDCLASS(CellStructure, Node)


protected:
	static void _bind_methods();



public:
	CellStructure();
	~CellStructure();

	virtual void activate(CellState *);

	void setCreationNutrientCost(const float);
	float getCreationNutrientCost() const;

	void setMaintenanceNutrientCost(const float);
	float getMaintenanceNutrientCost() const;

private:
	float _creationNutrientCost;
	float _maintenanceNutrientCost;
};