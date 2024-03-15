#pragma once

#include "environment.hpp"
#include "cell.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

class NutrientZone : public Area2D {
    GDCLASS(NutrientZone, Area2D)

protected:
    static void _bind_methods();

public:
    NutrientZone();
    ~NutrientZone();

    void applyScale(const float);
    float getScale() const;

    void setPosition(const float); // Placeholder type
    float getPosition() const;

    Size2 getSpriteSize() const;

    void _feeding_cells(Vector<Cell> *cell);
    void _on_body_entered(Node *body);
    void _on_body_exited(Node *body);
    void _process(const float);

private:
    float _scale;
    float _position;

    NutrientZone *_nutrientZone;
    Size2 _spriteSize;
};