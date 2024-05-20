# LineageGraphVertex Description

## Classes

LineageGraphVertex
Inherits: none
Inherited by: none

Description: a vertex in a lineage graph that holds a reference to a Cell, its parents, and its children

### Properties
- _cell (Cell *): a reference to a Cell tracked by the LineageGraph to which this vertex belongs
- _parents (Vector<LineageGraphVertex *>): a list of references to vertices holding the parents of the stored Cell
- _children (Vector<LineageGraphVertex *>): a list of references to vertices holding the children of the stored Cell

### Methods
- void setCell(Cell *cell): sets _cell to the given value
- Cell *getCell() const: returns _cell

- int getIndegree() const: returns the number of parents of this vertex
- int getOutdegree() const: returns the number of children of this vertex
- int getDegreeSum() const: returns the sum of the parents and children of this vertex

- void linkToParent(LineageGraphVertex *parent): adds the given vertex as a parent of this vertex
- void removeLinkToParent(LineageGraphVertex *parent): removes the given vertex from the list of parents of this vertex

- LineageGraphVertex *getParent(Cell *parent) const: returns the vertex that holds the given Cell reference if present _parents
- Vector<LineageGraphVertex *> getParents() const: returns the list of parents of this vertex (_parents)

- int indexOfParent(Cell *) const: returns the index of the parent vertex that holds the given Cell reference if present in _parents
- int indexOfParent(LineageGraphVertex *) const: returns the index of the given vertex if present in _parents

- void linkToChild(LineageGraphVertex *): adds the given vertex as a child of this vertex
- void removeLinkToChild(LineageGraphVertex *): removes the given vertex from the list of children of this vertex

- LineageGraphVertex *getChild(Cell *) const: returns the vertex that holds the given Cell reference if present in _children
- Vector<LineageGraphVertex *> getChildren() const: returns the list of children of this vertex (_children)

- int indexOfChild(Cell *) const: returns the index of the child vertex that holds the given Cell reference if present in _children
- int indexOfChild(LineageGraphVertex *) const: returns the index of the given vertex if present in _children

## Non-Member Functions
None
