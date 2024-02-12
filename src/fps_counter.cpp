#include "fps_counter.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void FpsCounter::_bind_methods() {}

FpsCounter::FpsCounter() {}
FpsCounter::~FpsCounter() {}

bool run = 0;

void FpsCounter::start_fps() {
	run = 1;
	return;
}

void FpsCounter::_process(double delta) {
	// Don't run if in editor
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (run) {
		const String fps =
				"FPS " + String::num(Engine::get_singleton()->get_frames_per_second());
		set_text(fps);
	}
}