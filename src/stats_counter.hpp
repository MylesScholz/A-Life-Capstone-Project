#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/label.hpp>

using namespace godot;

class StatsCounter : public Label {
	GDCLASS(StatsCounter, Label)

protected:
	static void _bind_methods();

public:
	StatsCounter();
	~StatsCounter();

	void _process(double delta) override;
};