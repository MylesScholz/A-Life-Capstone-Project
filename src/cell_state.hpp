#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/templates/vector.hpp>

using namespace godot;

class CellState : public Node {
	GDCLASS(CellState, Node)

protected:
	static void _bind_methods();

public:
	CellState();
	~CellState();

	void setAlive(const bool);
	bool getAlive() const;

	void increaseProtectedGenes(const int);
	int getProtectedGenes();
	void resetProtectedGenes();

	void setBirthTime(const int);
	float getBirthTime() const;

	void setAge(const float);
	float getAge() const;
	void increaseAge(const float);

	void setLifespan(const float);
	float getLifespan() const;

	void setScale(const float);
	void applyScale(const float);
	float getScale() const;

	void setNutrientEnergyConversionRate(const float);
	float getNutrientEnergyConversionRate() const;

	void setHomeostasisNutrientCost(const float);
	float getHomeostasisNutrientCost() const;

	void setReproductionNutrientCost(const float);
	float getReproductionNutrientCost() const;

	void setGrowthNutrientCost(const float);
	float getGrowthNutrientCost() const;

	void setTotalNutrients(const float);
	void incrementTotalNutrients(const float);
	float getTotalNutrients() const;

	void setNutrientMaximum(const float);
	float getNutrientMaximum() const;

	void setHomeostasisEnergyCost(const float);
	float getHomeostasisEnergyCost() const;

	void setReproductionEnergyCost(const float);
	float getReproductionEnergyCost() const;

	void setGrowthEnergyCost(const float);
	float getGrowthEnergyCost() const;

	void setTotalEnergy(const float);
	void incrementTotalEnergy(const float);
	float getTotalEnergy() const;

	void setEnergyMaximum(const float);
	float getEnergyMaximum() const;

	void setGrowthRate(const float);
	float getGrowthRate() const;

	void setNextMovementVector(const Vector2);
	Vector2 getNextMovementVector() const;

	void setReceptorVectors(const Vector<Vector2>);
	Vector<Vector2> getReceptorVectors() const;

	void addMutationChance(const float);
	float getMutationChance(const int);
	int getMutationChanceCount() const;

	void _ready() override;

private:
	bool _alive;
	int _protectedGenes;
	float _age;
	float _birthTime;
	float _deathTime;
	float _lifespan;
	float _scale;
	float _nutrientEnergyConversionRate;
	float _homeostasisNutrientCost;
	float _reproductionNutrientCost;
	float _growthNutrientCost;
	float _totalNutrients;
	float _nutrientMaximum;
	float _homeostasisEnergyCost;
	float _reproductionEnergyCost;
	float _growthEnergyCost;
	float _totalEnergy;
	float _energyMaximum;
	float _growthRate;
	Vector2 _nextMovementVector;
	Vector<Vector2> _receptorVectors;
	Vector<float> _mutationChances;
};