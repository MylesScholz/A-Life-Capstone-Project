#pragma once

#include <godot_cpp/classes/Engine.hpp>
#include <godot_cpp/classes/Label.hpp>

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