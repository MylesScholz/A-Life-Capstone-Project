# Receptor Description

## Classes

Receptor
Inherits: Area2D  
Inherited by: none

Description: the Receptor class is a CellStructure that represents a single nutrient-detecting receptor in a CellMembrane

### Properties
- _sprite (Sprite2D *): a pointer to the Sprite2D node for this Receptor

### Methods
- void _on_area_entered(Area2D *area): a signal callback function that triggers when this Receptor collides with another Area2D; emits a receptor_activated signal if the Area2D is a NutrientZone
- void _on_area_exited(Area2D *area): a signal callback function that triggers when this Receptor stops colliding with another Area2D; emits a receptor_deactivated signal if the Area2D is a NutrientZone

- void setSprite(Sprite2D *sprite): sets _sprite to the given value
- Sprite2D *getSprite(): returns _sprite

- void _ready(): runs once when this object is created and ready to use; sets this Receptor's sprite property to a child Sprite2D node; also connects signals to callback functions

## Non-Member Functions
None
