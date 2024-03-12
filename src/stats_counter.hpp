#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class StatsCounter : public VBoxContainer {
	GDCLASS(StatsCounter, VBoxContainer)

protected:
	static void _bind_methods();

public:
	StatsCounter();
	~StatsCounter();

	void _ready() override;
	void StatsCounter::_update_Stats(Variant cell_instance);
	void clear_stats();
	void add_label(String text);

	void _process(double delta) override;
};