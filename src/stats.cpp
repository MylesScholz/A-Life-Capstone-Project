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
}