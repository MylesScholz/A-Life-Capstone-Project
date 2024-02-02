#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/label.hpp>

namespace godot {

class FpsCounter : public Label {
	GDCLASS(FpsCounter, Label)

protected:
	static void _bind_methods();

public:
	FpsCounter();
	~FpsCounter();

	void _process(double) override;
};

} // namespace godot