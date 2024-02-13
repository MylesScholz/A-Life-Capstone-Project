# StartButton Description

## Classes
ResetButton
Inherits: TexturedButton  
Inherited by: none

Description: The main menu button is a UI element that triggers the simulation reset all ui elements back to the main menu.

### Properties
None

### Methods
- void _pressed(): Uses CellSpawner to kill all Cells and then finds and makes all current ui elements invisible while reopening the main menu and spawns background cells. It also resets statistics like time and collisions.

## Non-Member Functions
None
