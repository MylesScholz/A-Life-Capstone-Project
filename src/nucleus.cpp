#include "nucleus.hpp"

using namespace godot;

void Nucleus::_bind_methods() {
	//Reproduction Threshold Variable
	ClassDB::bind_method(D_METHOD("set_reproThreshold", "reproductionThreshold"),
			&Nucleus::setReproThreshold);
	ClassDB::bind_method(D_METHOD("get_reproThreshold"), &Nucleus::getReproThreshold);
	ClassDB::add_property("Nucleus", PropertyInfo(Variant::FLOAT, "Reproduction Threshold"),
			"set_reproThreshold", "get_reproThreshold");
}

Nucleus::Nucleus() {
	_alive = true;
	_lifespan = 1.;
	_homeostasisCost = 1.;
	_reproCost = 1.;
	_reproThreshold = 2.;
}

Nucleus::~Nucleus() {
}

void Nucleus::setAlive(const bool alive) {
	_alive = alive;
}

bool Nucleus::getAlive() const {
	return _alive;
}

float Nucleus::getBirthTime() const {
	return _birthTime;
}

void Nucleus::setLifespan(const float lifespan) {
	if (lifespan > 0) {
		_lifespan = lifespan;
	}
}

float Nucleus::getLifespan() const {
	return _lifespan;
}

void Nucleus::setHomeostasisCost(const float hCost) {
	if (hCost > 0) {
		_homeostasisCost = hCost;
	}
}

float Nucleus::getHomeostasisCost() const {
	return _homeostasisCost;
}

void Nucleus::setReproCost(const float rCost) {
	if (rCost > 0) {
		_reproCost = rCost;
	}
}

float Nucleus::getReproCost() const {
	return _reproCost;
}

void Nucleus::setReproThreshold(const float rThreshold) {
	if (rThreshold > 0) {
		_reproThreshold = rThreshold;
	}
}

float Nucleus::getReproThreshold() const {
	return _reproThreshold;
}