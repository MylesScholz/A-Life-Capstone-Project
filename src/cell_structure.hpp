#pragma once

#include "cell_state.hpp"

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

using namespace godot;

class CellStructure : public Node2D {
	GDCLASS(CellStructure, Node2D)

protected:
	static void _bind_methods();

public:
	CellStructure();
	~CellStructure();

	virtual void activate(CellState *);
	virtual void modify(String, float);
	virtual void applyScale(const float);

	void setCreationNutrientCost(const float);
	float getCreationNutrientCost() const;

	void setMaintenanceNutrientCost(const float);
	float getMaintenanceNutrientCost() const;

	void setCreationEnergyCost(const float);
	float getCreationEnergyCost() const;

	void setMaintenanceEnergyCost(const float);
	float getMaintenanceEnergyCost() const;

	float getScale() const;

	void setSprite(AnimatedSprite2D *);
	AnimatedSprite2D *getSprite();
	Size2 getSpriteSize();

private:
	float _creationNutrientCost;
	float _maintenanceNutrientCost;
	float _creationEnergyCost;
	float _maintenanceEnergyCost;
	float _scale;
	AnimatedSprite2D *_sprite;
};