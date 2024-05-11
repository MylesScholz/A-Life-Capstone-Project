#pragma once
#include "cell.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Stats : public VBoxContainer {
	GDCLASS(Stats, VBoxContainer)

protected:
	static void _bind_methods();

public:
	Stats();
	~Stats();

	void _ready() override;
	void _process(double delta) override;
	void _update_Stats(Variant cell_instance);
	void _set_selected_cell(Variant cell_instance);
	Cell *get_selected_cell();
	void _clear_selected_cell();
	void clear_stats();
	void update_label(String name, String text);
	Label *add_label(String name, String text);
	String format_decimal(double value, int decimal_places);

private:
	Cell *selected_cell = nullptr;
	int update_counter = 0;
	bool has_swapped = false;
};