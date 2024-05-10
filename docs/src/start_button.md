# StartButton Description

## Classes
StartButton
Inherits: Button  
Inherited by: none

Description: The start button is a UI element that triggers the simulation to start by spawning cells.

### Properties
None

### Methods
- void _ready(): runs once when the StartButton enters the node tree; sets the button text to "Start"
- void _pressed(): runs when the button is pressed; uses CellSpawner to create Cells and then becomes invisible

## Non-Member Functions
None
