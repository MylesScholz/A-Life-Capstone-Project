#pragma once

#include "cell_structure.hpp"

using namespace godot;

class Mitochondria : public CellStructure {
	GDCLASS(Mitochondria, CellStructure);

protected:
	static void _bind_methods();

public:
	Mitochondria();
	~Mitochondria();

	void activate(CellState *) override;
	void modify(String, float) override;

	void setActivationThreshold(const float);
	float getActivationThreshold() const;

	void setStrength(const float);
	float getStrength() const;

	void setEfficiency(const float);
	float getEfficiency() const;

	void setPreferredConversionRate(const float);
	float getPreferredConversionRate() const;

	void setActivationResource(const String);
	String getActivationResource() const;

	void setThresholdType(const String);
	String getThresholdType() const;

	void _ready() override;

private:
	float _activationThreshold;
	float _strength;
	float _efficiency;
	float _preferredConversionRate;
	String _activationResource;
	String _thresholdType;
};
