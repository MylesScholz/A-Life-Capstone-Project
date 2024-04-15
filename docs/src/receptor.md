# Receptor Description

## Classes

Receptor
Inherits: Area2D  
Inherited by: none

Description: the Receptor class is a CellStructure that represents a single nutrient-detecting receptor in a CellMembrane

### Properties
- _baseSpriteScale (float): the sprite scaling corresponding to a 1.0 scale Cell; this value must match the value set in the Godot editor
- _sprite (AnimatedSprite2D *): a pointer to the AnimatedSprite2D node for this Receptor; switches frames when activated/deactivated

### Methods
- void _on_area_entered(Area2D *area): a signal callback function that triggers when this Receptor collides with another Area2D; emits a receptor_activated signal if the Area2D is a NutrientZone; sets _sprite to its activated frame
- void _on_area_exited(Area2D *area): a signal callback function that triggers when this Receptor stops colliding with another Area2D; emits a receptor_deactivated signal if the Area2D is a NutrientZone; sets _sprite to its deactivated frame

- void setScale(const float scale): sets this Receptor's scale to the given value multiplied by _baseSpriteScale

- void setSprite(Sprite2D *sprite): sets _sprite to the given value
- Sprite2D *getSprite(): returns _sprite

- void _ready(): runs once when this object is created and ready to use; sets this Receptor's sprite property to a child Sprite2D node; also connects signals to callback functions

## Non-Member Functions
None
