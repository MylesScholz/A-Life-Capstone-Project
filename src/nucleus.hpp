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

	void setAlive(const bool);
	bool getAlive() const;

	float getBirthTime() const;

	void setLifespan(const float);
	float getLifespan() const;

	void setHomeostasisCost(const float);
	float getHomeostasisCost() const;

	void setReproCost(const float);
	float getReproCost() const;

	void setReproThreshold(const float);
	float getReproThreshold() const;

private:
	bool _alive;
	float _birthTime;
	float _lifespan;
	float _homeostasisCost;
	float _reproCost;
	float _reproThreshold;
};

} //namespace godot

#endif