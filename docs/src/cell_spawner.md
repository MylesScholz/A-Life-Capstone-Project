# CellSpawner Description

## Classes

CellSpawner
Inherits: Node  
Inherited by: none  

Description: the CellSpawner is the root node of the project's main scene, containing the CellEnvironment and the UI. It instantiates Cells in the CellEnvironment when triggered by various UI events.

### Properties
- _cellScene (Ref\<PackedScene\>): a reference to a Godot scene containing a Cell node which will be instantiated by the CellSpawner
- rand (Ref\<RandomNumberGenerator\>): a reference to a random number generator object; used for randomized cell placement, scaling, and initial force
- _numCells (int): the number of cells to spawn; written to by the Godot Editor
- _minForce (float): the lower bound of the random initial force applied to cells; written to by the Godot Editor
- _maxForce (float): the upper bound of the random initial force applied to cells; written to by the Godot Editor
- _resourceProportion (float): the proportion of maximum resources that Cells will spawn with; written to by the Godot Editor

### Methods
- void setNumCells(const int numCells): sets _numCells to the given value
- int getNumCells() const: returns _numCells

- void setCellScene(const Ref\<PackedScene\> cellScene): sets _cellScene to the given value
- Ref\<PackedScene\> getCellScene() const: returns _cellScene

- void setMinForce(const float minForce): sets _minForce to the given value; does not allow _minForce > _maxForce
- float getMinForce()const: returns _minForce

- void setMaxForce(const float maxForce): sets _maxForce to the given value; does not allow _maxForce < _minForce
- float getMaxForce() const: returns _maxForce

- void setResourceProportion(const float resourceProportion): sets _resourceProportion to the given value if it is in [0, 1]
- float getResourceProportion() const: returns _resourceProportion

- void spawnCell(bool isImmortal): instantiates one Cell as a child of this Node; Cell placement, scaling, and initial force are randomized; Cell immortality is set to isImmortal

- void _ready() override: runs once when the CellSpawner enters the node tree; disables this object running in the Godot Editor; connects setNumCells() and setResourceProportion() to their respective setting in the InitalValues menu within the UI; spawns NutrientZones
- void _on_cell_reproduction(Cell *cell): runs when a cell signals to reproduce. It then spawns a new cell which is a copy of the original. This is where mutation will take place once we implement it.

## Non-Member Functions
None
