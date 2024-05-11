#include "stats.hpp"
#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <iomanip>
#include <sstream>

#include "helpers.hpp"

using namespace godot;

void Stats::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_clear_selected_cell"), &Stats::_clear_selected_cell);
	ADD_SIGNAL(MethodInfo("cell_selected", PropertyInfo(Variant::OBJECT, "cell")));
}

Stats::Stats() {}
Stats::~Stats() {}

void Stats::_process(double delta) {
	DONT_RUN_IN_EDITOR;

	static double time_since_last_update = 0.0;
	time_since_last_update += delta;

	if (selected_cell && time_since_last_update >= 0.5) {
		_update_Stats(selected_cell);
		time_since_last_update = 0.0;
	}
}

void Stats::_ready() {
	set_process_mode(Node::PROCESS_MODE_ALWAYS);
}

void Stats::_set_selected_cell(Variant cell_instance) {
	UtilityFunctions::print("assignment detected");
	selected_cell = Object::cast_to<Cell>(cell_instance);
}
Cell *Stats::get_selected_cell() { return selected_cell; }

void Stats::_clear_selected_cell() {
	UtilityFunctions::print("clear detected");
	selected_cell = nullptr;
	clear_stats();
}

String Stats::format_decimal(double value, int decimal_places) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(decimal_places) << value;
	return stream.str().c_str();
}

void Stats::_update_Stats(Variant cell_instance) {
	Array stats = cell_instance.call("getStats");
	update_label("StatLabel_1", " Birth Time: " + format_decimal(stats[0], 3));
	update_label("StatLabel_2", " Alive: " + String(stats[1]));
	update_label("StatLabel_3", " Age: " + format_decimal(stats[2], 3));
	update_label("StatLabel_4", " Energy: " + format_decimal(stats[3], 3));
	update_label("StatLabel_5", " Nutrients: " + format_decimal(stats[4], 3));
	update_label("StatLabel_6", " Mass: " + format_decimal(stats[5], 3) + " µg");
	update_label("StatLabel_7", " Size: " + format_decimal(stats[6], 3) + " µm");
}

void Stats::update_label(String name, String text) {
	NodePath path(name);
	Label *label = get_node<Label>(path);
	if (!label) {
		label = add_label(name, text);
	}
	label->set_text(text);
}

Label *Stats::add_label(String name, String text) {
	Label *label = new Label();
	label->set_name(name);
	label->set_text(text);
	add_child(label);
	return label;
}

void Stats::clear_stats() {
	Array children = get_children();
	for (int i = 0; i < children.size(); ++i) {
		Label *child = Object::cast_to<Label>(children[i]);
		// Check if the cast was successful
		if (child) {
			remove_child(child);
			// Optionally, queue the child for deletion
			child->queue_free();
		}
	}
}