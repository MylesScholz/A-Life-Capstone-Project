# CellStructure Description

## Classes

CellStructure
Inherits: Node  
Inherited by: Nucleus, Mitochondria, Ribosomes, Flagella  

Description: an abstract class representing physical cell components in general

### Properties
- _creationNutrientCost (float): the amount of nutrients expended when creating this CellStructure
- _maintenanceNutrientCost (float): the amount of nutrients expend per second to maintain this CellStructure's functionality
- _creationEnergyCost (float): the amount of energy expended when creating this CellStructure
- _maintenanceEnergyCost (float): the amount of energy expend per second to maintain this CellStructure's functionality

### Methods
- virtual void activate(CellState *cellState): an empty method which should contain component activation checking and behavior in child classes

- void applyScale(const float scale): applies the given linear scaling ratio to the CellStructure's sprite

- void setCreationNutrientCost(const float creationNutrientCost): sets _creationNutrientCost to the given value if it is > 0.0
- float getCreationNutrientCost() const: returns _creationNutrientCost

- void setMaintenanceNutrientCost(const float maintenanceNutrientCost): sets _maintenanceNutrientCost to the given value if it is > 0.0
- float getMaintenanceNutrientCost() const: returns _maintenanceNutrientCost

- void setCreationEnergyCost(const float creationEnergyCost): sets _creationEnergyCost to the given value if it is > 0.0
- float getCreationEnergyCost() const: returns _creationEnergyCost

- void setMaintenanceEnergyCost(const float maintenanceEnergyCost): sets _maintenanceEnergyCost to the given value if it is > 0.0
- float getMaintenanceEnergyCost() const: returns _maintenanceEnergyCost

- void setSprite(Sprite2D *): sets _sprite to the given value
- Sprite2D *getSprite(): returns _sprite

## Non-Member Functions
None
