#pragma once


#include "cell_state.hpp"

#include <godot_cpp/classes/sprite2d.hpp>

using namespace godot;

class CellStructure : public Node2D {
	GDCLASS(CellStructure, Node2D)


protected:
	static void _bind_methods();



public:
	CellStructure();
	~CellStructure();

	virtual void activate(CellState *);

	void applyScale(const float);

	void setCreationNutrientCost(const float);
	float getCreationNutrientCost() const;

	void setMaintenanceNutrientCost(const float);
	float getMaintenanceNutrientCost() const;

	void setCreationEnergyCost(const float);
	float getCreationEnergyCost() const;

	void setMaintenanceEnergyCost(const float);
	float getMaintenanceEnergyCost() const;

	void setSprite(Sprite2D *);
	Sprite2D *getSprite();

private:
	float _creationNutrientCost;
	float _maintenanceNutrientCost;
	float _creationEnergyCost;
	float _maintenanceEnergyCost;
	Sprite2D *_sprite;
};