# CellState Description

## Classes

CellState
Inherits: Node  
Inherited by: none

Description: the CellState Node is a manager for the Cell's state variables, such as scale, age, and lifespan.

### Properties
- _alive (bool): whether the Cell is alive or not
- _age (float): the time in seconds that the Cell has spent alive
- _birthTime (float): the time in seconds when the Cell was "born"
- _deathTime (float): the time in seconds when the Cell died
- _lifespan (float): the time threshold beyond which the Cell has a chance to die
- _scale (float): the proportion of the Cell's default size that the Cell currently is
- _nutrientEnergyConversionRate (float): the ratio of nutrients to energy used by Mitochondria and Ribosomes in the Cell when converting between them
- _homeostasisNutrientCost (float): the cost in nutrients to keep the Cell alive; summed from the maintenance costs of the Cell's CellStructures
- _reproductionNutrientCost (float): the cost in nutrients expended when the Cell reproduces; summed form the creation costs of the Cell's CellStructures
- _growthNutrientCost (float): the cost in nutrients per unit area expended when the Cell grows
- _totalNutrients (float): the amount of nutrients stored in the Cell
- _nutrientMaximum (float): the maximum amount of nutrients the Cell can hold at one time
- _homeostasisEnergyCost (float): the cost in energy to keep the Cell alive; summed from the maintenance costs of the Cell's CellStructures
- _reproductionEnergyCost (float): the cost in energy expended when the Cell reproduces; summed form the creation costs of the Cell's CellStructures
- _growthEnergyCost (float): the cost in energy per unit area expended when the Cell grows
- _totalEnergy (float): the amount of energy stored in the Cell
- _energyMaximum (float): the maximum amount of energy the Cell can hold at one time
- _growthRate (float): the scaling ratio applied to the Cell when it grows
- _nextMovementVector (Vector2): the force vector applied to the Cell by its Flagella
- _receptorVectors (Vector\<Vector2\>): a dynamic list of position vectors of the currently activated Receptors in the Cell's CellMembrane

### Methods
- void setAlive(const bool alive): sets _alive to the given value
- bool getAlive() const: returns _alive

- void setBirthTime(const int currentMsec): sets _birthTime to the given millisecond / 1000.0
- float getBirthTime() const: returns _birthTime

- void setAge(const float age): sets _age to the given value if it is >= 0
- float getAge(const int currentMsec) const: returns the difference in seconds between the given millisecond and _birthTime
- void increaseAge(const float delta): increments _age by the given value

- void setLifespan(const float lifespan): sets _lifespan to the given value; lifespan must be greater than zero
- float getLifespan() const: returns _lifespan

- void setScale(const float scale): sets _scale to the given value
- void applyScale(const float scale): applies a linear scaling to _scale; scale must be greater than 0
- float getScale() const: returns _scale

- void setHomeostasisNutrientCost(const float homeostasisNutrientCost): sets _homeostasisNutrientCost to the given value if it is > 0.0
- float getHomeostasisNutrientCost() const: returns _homeostasisNutrientCost

- void setReproductionNutrientCost(const float reproductionNutrientCost): sets _reproductionNutrientCost to the given value if it is > 0.0
- float getReproductionNutrientCost() const: returns _reproductionNutrientCost

- void setGrowthNutrientCost(const float growthNutrientCost): sets _growthNutrientCost to the given value if it is >= 0.0
- float getGrowthNutrientCost() const: returns _growthNutrientCost

- void setTotalNutrients(const float totalNutrients): sets _totalNutrients to the given value, within [0.0, _nutrientMaximum]
- void incrementTotalNutrients(const float nutrients): increments _totalNutrients by the given value, where the sum is in [0.0, _nutrientMaximum]
- float getTotalNutrients() const: returns _totalNutrients

- void setNutrientMaximum(const float nutrientMaximum): sets _nutrientMaximum to the given value if it is >= 0.0
- float getNutrientMaximum() const: returns _nutrientMaximum

- void setHomeostasisEnergyCost(const float homeostasisEnergyCost): sets _homeostasisEnergyCost to the given value if it is > 0.0
- float getHomeostasisEnergyCost() const: returns _homeostasisEnergyCost

- void setReproductionEnergyCost(const float reproductionEnergyCost): sets _reproductionEnergyCost to the given value if it is > 0.0
- float getReproductionEnergyCost() const: returns _reproductionEnergyCost

- void setGrowthEnergyCost(const float growthEnergyCost): sets _growthEnergyCost to the given value if it is >= 0.0
- float getGrowthEnergyCost() const: returns _growthEnergyCost

- void setTotalEnergy(const float totalEnergy): sets _totalEnergy to the given value, within [0.0, _energyMaximum]
- void incrementTotalEnergy(const float energy): increments _totalEnergy by the given value, where the sum is in [0.0, _energyMaximum]
- float getTotalEnergy() const: returns _totalEnergy

- void setEnergyMaximum(const float energyMaximum): sets _energyMaximum to the given value if it is >= 0.0
- float getEnergyMaximum() const: returns _energyMaximum

- void setGrowthRate(const float): sets _growthRate to the given value if it is > 1
- float getGrowthRate() const: returns _growthRate

- void setNextMovementVector(const Vector2): sets _nextMovementVector to the given value
- Vector2 getNextMovementVector() const: returns _nextMovementVector

- void setReceptorVectors(const Vector<Vector2>): sets _receptorVectors to the given value
- Vector<Vector2> getReceptorVectors() const: returns _receptorVectors

- void _ready() override: runs once when the CellState enters the node tree; sets _birthTime to the current simulation second; calls setLifespan(), setGrowthNutrientCost() and setGrowthEnergyCost() with their respective setting in the InitalValues menu within the UI

## Non-Member Functions
None
