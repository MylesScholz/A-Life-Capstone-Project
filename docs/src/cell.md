# Cell Description

## Classes

Cell
Inherits: RigidBody2D  
Inherited by: none

Description: The Cell object represents a biological cell within a simulation. It contains some attributes and behaviors directly, and it delegates others to subnodes, such as CellState.

### Properties
- CollisionCount (static int): the static counter for the number of Cell collisions in the simulaton
- _spriteSize (Size2): the rectangular area covered by the Cell's sprite; stored here for ease of use when spawning Cells
- _cellState (CellState *): a pointer to the Cell's CellState object, which manages internal information about the Cell
- _cellStructures (Vector\<CellStructure *\> ): a vector of pointers to this Cell's CellStructures
- rand (Ref\<RandomNumberGenerator\>): a reference to a random number generator object; used for determining Cell death

### Methods
- void seteq(Cell* otherCell): copies over all aspects of another cell to this one. Used during reproduction to match a child cell to its parent
- void applyScale(const float scale): applies a linear scaling to the Cell; updates the Sprite2D, CollisionShape2D, CellState, and _spriteSize
- float getScale() const: returns the scale property of the cell (from CellState)

- Size2 getSpriteSize() const: returns the rectangular area of the Cell's sprite

- void _ready() override: runs once when the Cell has been created and is ready to be used; points _cellState to this Cell's CellState Node
- void _process(double delta) override: runs once per in-game frame; delta stores the real time since the last frame; simulates CellStructure activation and Cell aging, starvation, and death
- void _on_body_entered(Node *body): runs when another Node collides with this one; increments CollisionCount

## Non-Member Functions
None