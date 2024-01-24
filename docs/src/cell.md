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
- rand (Ref\<RandomNumberGenerator\>): a reference to a random number generator object; used for determining Cell death

### Methods
- void applyScale(float scale): applies a linear scaling to the Cell; updates the Sprite2D, CollisionShape2D, CellState, and _spriteSize
- float getScale(): returns the scale property of the cell (from CellState)
- Size2 getSpriteSize(): returns the rectangular area of the Cell's sprite
- void _ready(): runs once when the Cell has been created and is ready to be used
- void _process(double delta): runs once per in-game frame; delta stores the real time since the last frame; simulates Cell aging and death
- void _on_body_entered(Node *body): runs when another Node collides with this one; increments CollisionCount

## Non-Member Functions
None