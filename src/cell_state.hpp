#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/time.hpp>

using namespace godot;

class CellState {
public:
	CellState();
	~CellState();

	void setAlive(const bool);
	bool getAlive() const;

	void setBirthTime(const int);
	float getBirthTime() const;
	float getAge(const int) const;

	void setLifespan(const float);
	float getLifespan() const;

	void setScale(const float);
	void applyScale(const float);
	float getScale() const;

	void setHomeostasisNutrientCost(const float);
	float getHomeostasisNutrientCost() const;

	void setReproductionNutrientCost(const float);
	float getReproductionNutrientCost() const;

	void setTotalNutrients(const float);
	void incrementTotalNutrients(const float);
	float getTotalNutrients() const;

	void setNutrientMaximum(const float);
	float getNutrientMaximum() const;

	void setHomeostasisEnergyCost(const float);
	float getHomeostasisEnergyCost() const;

	void setReproductionEnergyCost(const float);
	float getReproductionEnergyCost() const;

	void setTotalEnergy(const float);
	void incrementTotalEnergy(const float);
	float getTotalEnergy() const;

	void setEnergyMaximum(const float);
	float getEnergyMaximum() const;

	void setNextMovementVector(const Vector2);
	Vector2 getNextMovementVector() const;

	void _ready() override;

private:
	bool _alive;
	float _birthTime;
	float _lifespan;
	float _scale;
	float _homeostasisNutrientCost;
	float _reproductionNutrientCost;
	float _totalNutrients;
	float _nutrientMaximum;
	float _homeostasisEnergyCost;
	float _reproductionEnergyCost;
	float _totalEnergy;
	float _energyMaximum;
	Vector2 _nextMovementVector;
};