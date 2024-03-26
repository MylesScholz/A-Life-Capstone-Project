#pragma once

#include "cell.hpp"

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class NutrientZone : public Area2D {
	GDCLASS(NutrientZone, Area2D)

protected:
	static void _bind_methods();

public:
	NutrientZone();
	~NutrientZone();

	void _on_body_entered(Node *);
	void _on_body_exited(Node *);

	void setTotalNutrients(const float);
	void incrementTotalNutrients(const float);
	float getTotalNutrients() const;

	void setNutrientMaximum(const float);
	float getNutrientMaximum() const;

	void setRegenerationRate(const float);
	float getRegenerationRate() const;

	void setFeedingRate(const float);
	float getFeedingRate() const;

	void _ready();
	void _process(float);

private:
	Vector<Cell *> _feedingCells;
	float _totalNutrients;
	float _nutrientMaximum;
	float _feedingRate;
	float _regenerationRate;
};