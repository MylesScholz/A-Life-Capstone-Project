#include "cell.hpp"

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Cell::_bind_methods() {
  ClassDB::bind_method(D_METHOD("apply_scale", "scale"), &Cell::applyScale);

  ClassDB::bind_method(D_METHOD("get_scale"), &Cell::getScale);
  ClassDB::bind_method(D_METHOD("get_sprite_size"), &Cell::getSpriteSize);
}

Cell::Cell() {
  rand.instantiate();

  _scale = 1;
  _spriteSize = Size2();
}
Cell::~Cell() {}

void Cell::applyScale(float scale) {
  if (scale <= 0)
    return;

  this->get_node<CollisionShape2D>("CollisionShape2D")
      ->apply_scale(Vector2(scale, scale));
  this->get_node<Sprite2D>("Sprite")->apply_scale(Vector2(scale, scale));
  _scale *= scale;
  _spriteSize = this->get_node<Sprite2D>("Sprite")->get_rect().size;
}

float Cell::getScale() const { return _scale; }

Size2 Cell::getSpriteSize() const { return _spriteSize; }

void Cell::_process(double delta) {
  // Don't run if in editor
  if (Engine::get_singleton()->is_editor_hint())
    return;
}