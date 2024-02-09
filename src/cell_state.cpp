#include "cell_state.hpp"

using namespace godot;

void CellState::_bind_methods() {
}

CellState::CellState() {
	_age = 0;
	_scale = 1;
}
CellState::~CellState() {
}

void CellState::setAlive(const bool alive) { _nucleus->setAlive(alive); }
bool CellState::getAlive() const { return _nucleus->getAlive(); }

void CellState::setMitochondria(Mitochondria *mitochondria) { _mitochondria = mitochondria; }
Mitochondria *CellState::getMitochondria() { return _mitochondria; }

void CellState::setNucleus(Nucleus* nucleus){
	_nucleus = nucleus;
}
Nucleus* CellState::getNucleus() const{
	return _nucleus;
}

void CellState::setAge(const float age) {
	if (age >= 0)
		_age = age;
}
void CellState::incrementAge(const float increment) {
	if (_age + increment > 0)
		_age += increment;
	else
		_age = 0;
}
float CellState::getAge() const { return _age; }


void CellState::setLifespan(const float lifespan) { _nucleus->setLifespan(lifespan);}
float CellState::getLifespan() const { return _nucleus->getLifespan(); }


void CellState::setScale(const float scale) { _scale = scale; }
void CellState::applyScale(const float scale) {
	if (scale <= 0)
		_scale *= scale;
}
float CellState::getScale() const { return _scale; }

void CellState::_ready() {
	_mitochondria = this->get_node<Mitochondria>("Mitochondria");
	_nucleus = this->get_node<Nucleus>("Nucleus");
}