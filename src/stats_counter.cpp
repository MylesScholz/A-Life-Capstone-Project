#include "stats_counter.hpp"
#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

#include "helpers.hpp"

void StatsCounter::_bind_methods() {}

StatsCounter::StatsCounter() {}
StatsCounter::~StatsCounter() {}

void StatsCounter::_process(double delta) {
	DONT_RUN_IN_EDITOR;

	const String stats = "COLLISIONS " + String::num(Cell::CollisionCount);
	set_text(stats);
}
