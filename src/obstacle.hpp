#pragma once

#include "environment.hpp"
#include "cell.hpp"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/area2d.hpp>

using namespace godot;

class Obstacle : public CollisionShape2D {
    GDCLASS(Obstacle, CollisionShape2D)

    protected:
        static void _bind_methods():

    public:
        Obstacle();
        ~Obstacle();

        void applyScale(const float);
        float getScale() const;

        void setPosition(const float); // Placeholder type
        float getPosition() const;

        Size2 getSpriteSize() const;

        void _ready() override;
        void _on_body_entered(Node *body);

    private:
        float _scale;
        float _position;

        Obstacle *_obstacle;
        Size2 _spriteSize;
};