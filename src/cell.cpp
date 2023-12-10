#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Cell::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &Cell::_on_body_entered);
}

int Cell::CollisionCount = 0; 

Cell::Cell() {

    // Setting default required parameters for collision detection on RigidBody2D objects, then applying the signal to Cell objects.
    this->set_contact_monitor(true);
    this->set_max_contacts_reported(1000); // Adjust max contacts as complexity increases.
    this->connect("body_entered", Callable(this, "_on_body_entered"));

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

// function updates on cell contacts. Increments counter for use in stats_counter.cpp
void Cell::_on_body_entered(Node *body) {
    CollisionCount++;
}
