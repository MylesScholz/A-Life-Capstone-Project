#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Cell::_bind_methods() {}

Cell::Cell() {
    rand.instantiate();
    force_magnitude = rand->randf_range(50.0, 150.0);

    float direction = rand->randf_range(0, 2 * Math_PI);
    Vector2 force = Vector2(0, -1).rotated(direction) * force_magnitude;
    apply_force(force);
}
Cell::~Cell() {}

void Cell::_process(double delta) {
    // Don't run if in editor
    if (Engine::get_singleton()->is_editor_hint())
        return;

    // float direction = rand->randf_range(0, 2 * Math_PI);
    // Vector2 force = Vector2(0, -1).rotated(direction) * speed;
    // apply_force(force);
}