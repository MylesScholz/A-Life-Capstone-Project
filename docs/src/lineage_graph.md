# LineageGraph Description

## Classes

LineageGraph
Inherits: none 
Inherited by: none

Description: a graph data structure that manages the full Cell history of the simulation

### Properties
- _nColumns (int): the number of columns to store Cells in
- _storageSpacing (int): units of space between Cells in storage
- _storageBasis (Vector2): the coordinates of the top left (first) position of Cell storage
- _vertices (Vector<LineageGraphVertex *>): all vertices in the graph
- _LUCA (LineageGraphVertex *): an empty vertex that is an ancestor to all Cells in the simulation

### Methods
- LineageGraphVertex *getLUCA() const: returns _LUCA
- Vector2 getLUCAPosition(): returns a position just above the first storage position (in case LUCA has a sprite)
- void updateLUCAEdges(): sets _LUCA as the parent of all vertices with no other parents

- Vector2 storeCell(Cell *cell): puts a Cell into storage
- Vector2 getCellPosition(Cell *cell): returns the position a Cell will have when in storage

- LineageGraphVertex *addVertex(Cell *cell): adds the given Cell reference as a LineageGraphVertex to the graph
- LineageGraphVertex *addVertex(LineageGraphVertex *vertex): adds the given vertex to the graph
- void removeVertex(Cell *keyCell): removes the given Cell reference from the graph if present
- void removeVertex(LineageGraphVertex *vertex): removes the given vertex from the graph

- LineageGraphVertex *getVertex(Cell *cell) const: returns the LineageGraphVertex that holds the given Cell reference if present
- Vector<LineageGraphVertex *> getVertices() const: returns the list of vertices in the graph (_vertices)

- void addEdge(Cell *parentCell, Cell *childCell): adds a symmetric parent-child connection between vertices holding the given Cell references; creates vertices if not present
- void removeEdge(Cell *parentCell, Cell *childCell): symmetrically removes a parent-child connection between the vertices holding the given Cell references

- int indexOfCell(Cell *keyCell) const: returns the index of the vertex in _vertices that holds the given Cell reference if present

## Non-Member Functions
None
