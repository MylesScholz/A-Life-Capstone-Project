# CellState Description

## Classes

CellState
Inherits: Node  
Inherited by: none

Description: the CellState Node is a manager for the Cell's state variables, such as scale, age, and lifespan.

### Properties
- _alive (bool): whether the cell is alive or not
- _age (float): the simulation-time age of the cell
- _lifespan (float): the time threshold beyond which the cell has a chance to die
- _scale (float): the proportion of the cell's default size that the cell currently is

### Methods
- void setAlive(const bool alive): sets _alive to the given value
- bool getAlive(): returns _alive
- void setAge(const float age): sets _age to the given value; does not allow negative ages
- void incrementAge(const float increment): adds increments to _age as long as the sum is greater than or equal to zero
- float getAge(): returns _age
- void setLifespan(const float lifespan): sets _lifespan to the given value; lifespan must be greater than zero
- float getLifespan(): returns _lifespan
- void setScale(const float scale): sets _scale to the given value
- void applyScale(const float scale): applies a linear scaling to _scale; scale must be greater than 0
- float getScale(): returns _scale

## Non-Member Functions
None
