#include "stats_counter.hpp"
#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void StatsCounter::_bind_methods(){}

StatsCounter::StatsCounter(){}
StatsCounter::~StatsCounter(){}

void StatsCounter::_process(double delta){
    // Don't run if in editor
    if(Engine::get_singleton()->is_editor_hint()) return;
    
    const String stats = "COLLISIONS " + String::num(Cell::CollisionCount);
    set_text(stats);
}
