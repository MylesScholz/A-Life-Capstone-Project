#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot {

class Mitochondria : public Node {
	GDCLASS(Mitochondria, Node);

protected:
	static void _bind_methods();

public:
	Mitochondria();
	~Mitochondria();

	void addNutrients(float);
	void decrementNutrients(const float);
	float getNutrients() const;
	void setNutrients(const float);

private:
	float _nutrients;
	float _nutrient_maximum;
	float _nutrient_efficiency;
};

}; // namespace godot