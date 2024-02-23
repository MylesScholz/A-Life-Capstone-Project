# CellState Description

## Classes

CellState
Inherits: Node  
Inherited by: none

Description: the CellState Node is a manager for the Cell's state variables, such as scale, age, and lifespan.

### Properties
- _alive (bool): whether the cell is alive or not
- _birthTime (float): the time in seconds when the cell was "born"
- _lifespan (float): the time threshold beyond which the cell has a chance to die
- _scale (float): the proportion of the cell's default size that the cell currently is

### Methods
- void setAlive(const bool alive): sets _alive to the given value
- bool getAlive() const: returns _alive

- void setBirthTime(const int currentMsec): sets _birthTime to the given millisecond / 1000.0
- float getBirthTime() const: returns _birthTime
- float getAge(const int currentMsec) const: returns the difference in seconds between the given millisecond and _birthTime

- void setLifespan(const float lifespan): sets _lifespan to the given value; lifespan must be greater than zero
- float getLifespan() const: returns _lifespan

- void setScale(const float scale): sets _scale to the given value
- void applyScale(const float scale): applies a linear scaling to _scale; scale must be greater than 0
- float getScale() const: returns _scale

- void setHomeostasisNutrientCost(const float homeostasisNutrientCost): sets _homeostasisNutrientCost to the given value if it is > 0.0
- float getHomeostasisNutrientCost() const: returns _homeostasisNutrientCost

- void setReproductionNutrientCost(const float reproductionNutrientCost): sets _reproductionNutrientCost to the given value if it is > 0.0
- float getReproductionNutrientCost() const: returns _reproductionNutrientCost

- void setTotalNutrients(const float totalNutrients): sets _totalNutrients to the given value, within [0.0, _nutrientMaximum]
- void incrementTotalNutrients(const float nutrients): increments _totalNutrients by the given value, where the sum is in [0.0, _nutrientMaximum]
- float getTotalNutrients() const: returns _totalNutrients

- void setNutrientMaximum(const float nutrientMaximum): sets _nutrientMaximum to the given value if it is >= 0.0
- float getNutrientMaximum() const: returns _nutrientMaximum

- void setHomeostasisEnergyCost(const float homeostasisEnergyCost): sets _homeostasisEnergyCost to the given value if it is > 0.0
- float getHomeostasisEnergyCost() const: returns _homeostasisEnergyCost

- void setReproductionEnergyCost(const float reproductionEnergyCost): sets _reproductionEnergyCost to the given value if it is > 0.0
- float getReproductionEnergyCost() const: returns _reproductionEnergyCost

- void setTotalEnergy(const float totalEnergy): sets _totalEnergy to the given value, within [0.0, _energyMaximum]
- void incrementTotalEnergy(const float energy): increments _totalEnergy by the given value, where the sum is in [0.0, _energyMaximum]
- float getTotalEnergy() const: returns _totalEnergy

- void setEnergyMaximum(const float energyMaximum): sets _energyMaximum to the given value if it is >= 0.0
- float getEnergyMaximum() const: returns _energyMaximum

- void _ready() override: runs once when the CellState has been created and is ready to be used; sets _birthTime to the current simulation second

## Non-Member Functions
None
