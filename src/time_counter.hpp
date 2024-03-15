#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/label.hpp>

namespace godot {

class TimeCounter : public Label {
	GDCLASS(TimeCounter, Label)

protected:
	static void _bind_methods();

public:
	TimeCounter();
	~TimeCounter();

	void toggle_time();

	void reset_time();

	void _process(double) override;
};

} // namespace godot