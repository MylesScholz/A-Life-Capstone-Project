#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Cell::_bind_methods(){}

Cell::Cell(){
    rand.instantiate();
    speed = rand->randf_range(150.0,250.0);
}
Cell::~Cell(){}

void Cell::_process(double delta){
    // Don't run if in editor
    if(Engine::get_singleton()->is_editor_hint()) 
        return;

    float direction = rand->randf_range(0,2 * Math_PI);
    Vector2 velocity = Vector2(0, -1).rotated(direction) * speed;
    set_position(get_position() + velocity * delta);
}