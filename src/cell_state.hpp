#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/time.hpp>

namespace godot {

class CellState : Node {
	GDCLASS(CellState, Node)

protected:
	static void _bind_methods();

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

private:
	bool _alive;
	float _birthTime;
	float _lifespan;
	float _scale;
	float _homeostasisNutrientCost;
	float _reproductionNutrientCost;
	float _totalNutrients;
	float _nutrientMaximum;
};

}; // namespace godot