#include "environment.hpp"
#include "cell.hpp"

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/core/class_db.hpp>

void NutrientZone::_bind_methods() {}

NutrientZone::NutrientZone() {
    _scale = 5.0;
    _position = 0.0;
}
NutrientZone::~NutrientZone() {}

void NutrientZone::applyScale(const float scale) { _scale = scale; }

float NutrientZone::getScale() const { return _nutrientZone->getScale(); }

void NutrientZone::setPosition(const float position) { _position = position; }
float NutrientZone::getPosition() const { return _nutrientZone->getPosition(); }

Size2 NutrientZone::getSpriteSize() const {}

void NutrientZone::_ready() {}

void NutrientZone::_on_body_entered() {}