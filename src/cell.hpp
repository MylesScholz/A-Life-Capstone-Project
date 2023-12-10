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

        static int CollisionCount;
        void _on_body_entered(Node *body);
        void _process(double delta) override;

    private:
        float force_magnitude;
        Ref<RandomNumberGenerator> rand;
    };

}
