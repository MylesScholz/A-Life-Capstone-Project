#include "obstacle.hpp"

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>

void Obstacle::_bind_methods() {}

Obstacle::Obstacle() {
    this->setPosition(0.0);
    this->applyScale(5.0);
}
Obstacle::~Obstacle() {}

void Obstacle::applyScale(const float scale) { _scale = scale; }

float Obstacle::getScale() const { return _obstacle->getScale(); }

void Obstacle::setPosition(const float position) { _position = position; }
float Obstacle::getPosition() const { return _obstacle->getPosition(); }

Size2 Obstacle::getSpriteSize() const {}

void Obstacle::_ready() {}

void Obstacle::_on_body_entered(Node body) {}