#include "fps_counter.hpp"

#include <godot_cpp/core/class_db.hpp>

#include "helpers.hpp"

void FpsCounter::_bind_methods() {}

FpsCounter::FpsCounter() {}
FpsCounter::~FpsCounter() {}

bool run = 0;

void FpsCounter::toggle_fps() {
	if (run) { // turn off
		run = 0;
		set_text("");
	} else { // turn on
		run = 1;
	}
	return;
}

void FpsCounter::_process(double delta) {
	DONT_RUN_IN_EDITOR;

	if (run) {
		const String fps =
				"FPS " + String::num(Engine::get_singleton()->get_frames_per_second());
		set_text(fps);
	}
}