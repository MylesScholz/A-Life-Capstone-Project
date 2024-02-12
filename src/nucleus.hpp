#ifndef NUCLEUS_HPP
#define NUCLEUS_HPP

#include <time.h>
#include <godot_cpp/classes/node.hpp>

namespace godot {

class Nucleus : public Node {
	GDCLASS(Nucleus, Node)

protected:
	static void _bind_methods();

public:
	Nucleus();
	~Nucleus();

	void setReproductionNutrientThreshold(const float);
	float getReproductionNutrientThreshold() const;

private:
	float _reproductionNutrientThreshold;
};

} //namespace godot

#endif