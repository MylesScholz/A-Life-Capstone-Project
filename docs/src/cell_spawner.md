# CellSpawner Description

## Classes

CellSpawner
Inherits: Node  
Inherited by: none  

Description: The cell spawner is a node in the base scene which instantiates cells into the simulation. It takes multiple properties from the base scene, including a separate cell scene, which acts as a template for the cells that will be instantiated.

### Properties
- _cellScene (Ref\<PackedScene\>): a reference to a Godot scene containing a Cell node which will be instantiated by the CellSpawner
- rand (Ref\<RandomNumberGenerator\>): a reference to a random number generator object; used for randomized cell placement, scaling, and initial force
- _numCells (int): the number of cells to spawn; written to by the Godot Editor
- _minForce (float): the lower bound of the random initial force applied to cells; written to by the Godot Editor
- _maxForce (float): the upper bound of the random initial force applied to cells; written to by the Godot Editor

### Methods
- void setNumCells(const int numCells): sets _numCells to the given value
- int getNumCells(): returns _numCells
- void setCellScene(const Ref\<PackedScene\> cellScene): sets _cellScene to the given value
- Ref\<PackedScene\> getCellScene(): returns _cellScene
- void setMinForce(const float minForce): sets _minForce to the given value; does not allow _minForce > _maxForce
- float getMinForce(): returns _minForce
- void setMaxForce(const float maxForce): sets _maxForce to the given value; does not allow _maxForce < _minForce
- float getMaxForce(): returns _maxForce
- void spawnCell(): instantiates one Cell scene as a child of this Node; Cell placement, scaling, and initial force are randomized
- void _ready(): runs once when the CellSpawner has been created and is ready to be used; disables this object running in the Godot Editor

## Non-Member Functions
None
