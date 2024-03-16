#include "time_counter.hpp"

#include <godot_cpp/core/class_db.hpp>

#include "helpers.hpp"

using namespace godot;

void TimeCounter::_bind_methods() {}

TimeCounter::TimeCounter() {}
TimeCounter::~TimeCounter() {}

static double total_time = 0.0;
bool start = 0;

void TimeCounter::toggle_time() {
	if (start) { // turn off
		start = 0;
		set_text("");
		this->reset_time();
	} else { // turn on
		start = 1;
	}
	return;
}

void TimeCounter::reset_time() {
	total_time = 0;
	return;
}

void TimeCounter::_process(double delta) {
	DONT_RUN_IN_EDITOR;

	if (this->get_text() == "-1") { // Communicate with GDScript
		this->toggle_time();
	}
	if (start) {
		total_time += delta; // Accumulate delta to track total time
		const String time =
				"Time: " + String::num(int(total_time)) + "s";
		set_text(time);
	}
}