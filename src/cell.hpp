#pragma once

#include <godot_cpp/classes/Engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/rigid_body2D.hpp>

namespace godot {

class Cell : public RigidBody2D {
  GDCLASS(Cell, RigidBody2D)

protected:
  static void _bind_methods();

public:
  Cell();
  ~Cell();

  void applyScale(float scale);

  float getScale() const;
  Size2 getSpriteSize() const;

  void _process(double delta) override;

private:
  float _scale;
  Size2 _spriteSize;
  Ref<RandomNumberGenerator> rand;
};

} // namespace godot