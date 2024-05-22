# LineageCamera Description

## Classes

LineageCamera
Inherits: Camera2D 
Inherited by: none

Description: an inset camera that controls the lineage display of the statistics panel

### Properties
- _selectCellPrompt (Label *): a reference to the cell selection prompt label
- _LUCAMessage (Label *): a reference to the "LUCA selected" message label
- _subViewportContainer (SubViewportContainer *): a reference to the subviewport container to which this camera belongs
- _parentButtonContainer (HFlowContainer *): a reference to the container for buttons that allow selection of Cell parents
- _childButtonContainer (HFlowContainer *): a reference to the container for buttons that allow selection of Cell children 

### Methods
- void selectCell(Cell *cell): updates the lineage tracking UI to focus on the given Cell
- void selectLUCA(): updates the lineage tracking UI to focus on the LUCA, which is not a real Cell
- void deselect(): resets the lineage tracking UI to an unselected state

- void fillButtonContainers(Cell *cell): adds buttons to _parentButtonContainer and _childButtonContainer for each parent and child of the given Cell, respectively
- void clearButtonContainers(): removes all buttons in _parentButtonContainer and _childButtonContainer

- void _ready() override: runs once when this object enters the node tree; sets the reference to UI items and sets their default visibility

## Non-Member Functions
None
