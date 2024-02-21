#pragma once

#include "cell_structure.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Ribosomes : public CellStructure {
	GDCLASS(Ribosomes, CellStructure)

protected:
	static void _bind_methods();

public:
	Ribosomes();
	~Ribosomes();

	void activate(CellState *) override;

	void setActivationThreshold(const float);
	float getActivationThreshold() const;

	void setStrength(const float);
	float getStrength() const;

	void setEfficiency(const float);
	float getEfficiency() const;

	void setConversionRate(const float);
	float getConversionRate() const;

	void setActivationResource(const String);
	String getActivationResource() const;

	void setThresholdType(const String);
	String getThresholdType() const;

	void _ready() override;

private:
	float _activationThreshold;
	float _strength;
	float _efficiency;
	float _conversionRate;
	String _activationResource;
	String _thresholdType;
};