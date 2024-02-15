#include "fps_counter.hpp"

#include <godot_cpp/core/class_db.hpp>

#include "helpers.hpp"

void FpsCounter::_bind_methods() {}

FpsCounter::FpsCounter() {}
FpsCounter::~FpsCounter() {}

void FpsCounter::_process(double delta) {
	DONT_RUN_IN_EDITOR;

	const String fps =
			"FPS " + String::num(Engine::get_singleton()->get_frames_per_second());
	set_text(fps);
}