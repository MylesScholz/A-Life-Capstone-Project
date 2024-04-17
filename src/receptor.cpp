#include "receptor.hpp"

void Receptor::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_area_entered", "area"), &Receptor::_on_area_entered);
	ClassDB::bind_method(D_METHOD("_on_area_exited", "area"), &Receptor::_on_area_exited);

	ADD_SIGNAL(MethodInfo("receptor_activated", PropertyInfo(Variant::OBJECT, "receptor")));
	ADD_SIGNAL(MethodInfo("receptor_deactivated", PropertyInfo(Variant::OBJECT, "receptor")));
}

Receptor::Receptor() {
	_nNutrientZones = 0;
	_baseSpriteScale = 0.15; // Must correspond to the Sprite2D scale value set in the Editor
}
Receptor::~Receptor() {}

void Receptor::_on_area_entered(Area2D *area) {
	if (area->get_class() == "NutrientZone") {
		_nNutrientZones++;

		this->emit_signal("receptor_activated", this);

		_sprite->set_frame(1);
	}
}
void Receptor::_on_area_exited(Area2D *area) {
	if (area->get_class() == "NutrientZone") {
		if (_nNutrientZones > 0)
			_nNutrientZones--;

		this->emit_signal("receptor_deactivated", this);

		if (_nNutrientZones == 0)
			_sprite->set_frame(0);
	}
}

void Receptor::setScale(const float scale) {
	if (scale <= 0)
		return;

	AnimatedSprite2D *sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (sprite)
		sprite->set_scale(Vector2(_baseSpriteScale * scale, _baseSpriteScale * scale));
}

int Receptor::getNNutrientZones() const { return _nNutrientZones; }

void Receptor::setSprite(AnimatedSprite2D *sprite) { _sprite = sprite; }
AnimatedSprite2D *Receptor::getSprite() { return _sprite; }

void Receptor::_ready() {
	// Connect the inherited area_entered and area_exited signals to the callbacks in this class
	this->connect("area_entered", Callable(this, "_on_area_entered"));
	this->connect("area_exited", Callable(this, "_on_area_exited"));

	AnimatedSprite2D *sprite = this->get_node<AnimatedSprite2D>("AnimatedSprite2D");
	if (sprite)
		this->setSprite(sprite);
}