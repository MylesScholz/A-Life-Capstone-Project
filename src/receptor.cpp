#include "receptor.hpp"

void Receptor::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_body_entered", "body"), &Receptor::_on_body_entered);
	ClassDB::bind_method(D_METHOD("_on_body_exited", "body"), &Receptor::_on_body_exited);

	ADD_SIGNAL(MethodInfo("receptor_activated", PropertyInfo(Variant::OBJECT, "receptor")));
	ADD_SIGNAL(MethodInfo("receptor_deactivated", PropertyInfo(Variant::OBJECT, "receptor")));
}

Receptor::Receptor() {}
Receptor::~Receptor() {}

void Receptor::_on_body_entered(Node *body) {
	if (body->get_class() == "Cell" || body->get_class() == "StaticBody2D")
		return;

	this->emit_signal("receptor_activated", this);
}
void Receptor::_on_body_exited(Node *body) {
	if (body->get_class() == "Cell" || body->get_class() == "StaticBody2D")
		return;

	this->emit_signal("receptor_deactivated", this);
}

void Receptor::setSprite(Sprite2D *sprite) { _sprite = sprite; }
Sprite2D *Receptor::getSprite() { return _sprite; }

void Receptor::_ready() {
	this->connect("body_entered", Callable(this, "_on_body_entered"));
	this->connect("body_exited", Callable(this, "_on_body_exited"));

	Sprite2D *sprite = this->get_node<Sprite2D>("Sprite2D");
	if (sprite)
		this->setSprite(sprite);
}