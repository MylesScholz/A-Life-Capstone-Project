#include "lineage_graph.hpp"

LineageGraph::LineageGraph() {
	// Number of columns of Cells in the storage area
	_nColumns = 5;
	// Storage basis vector; the top left position of the storage area; just to the right of the CellEnvironment
	_storageBasis = Vector2(1400, 0);
	// Spacing between Cells in the storage area
	_storageSpacing = 150;
	_vertices = Vector<LineageGraphVertex *>();
}
LineageGraph::~LineageGraph() {
	for (LineageGraphVertex *vertex : _vertices)
		delete vertex;
}

Vector2 LineageGraph::storeCell(Cell *cell) {
	// Initialize position at the storage basis vector
	Vector2 position = _storageBasis;

	int index = indexOfCell(cell);
	if (index < 0) {
		addVertex(cell);
		index = indexOfCell(cell);
	}

	position.x += (index % _nColumns) * _storageSpacing;
	position.y += (index / _nColumns) * _storageSpacing;

	cell->set_global_position(position);

	return position;
}

LineageGraphVertex *LineageGraph::addVertex(Cell *cell) {
	LineageGraphVertex *newVertex = new LineageGraphVertex(cell);

	_vertices.push_back(newVertex);
	return newVertex;
}
LineageGraphVertex *LineageGraph::addVertex(LineageGraphVertex *vertex) {
	if (_vertices.find(vertex) == -1)
		_vertices.push_back(vertex);

	return vertex;
}
void LineageGraph::removeVertex(Cell *keyCell) {
	int index = indexOfCell(keyCell);
	if (index < 0)
		return;

	LineageGraphVertex *vertex = _vertices.get(index);

	for (LineageGraphVertex *parent : vertex->getParents())
		parent->removeLinkToChild(vertex);

	for (LineageGraphVertex *child : vertex->getChildren())
		child->removeLinkToParent(vertex);

	_vertices.remove_at(index);
	delete vertex;
}
void LineageGraph::removeVertex(LineageGraphVertex *vertex) {
	int index = _vertices.find(vertex);
	if (index < 0)
		return;

	for (LineageGraphVertex *parent : vertex->getParents())
		parent->removeLinkToChild(vertex);

	for (LineageGraphVertex *child : vertex->getChildren())
		child->removeLinkToParent(vertex);

	_vertices.remove_at(index);
	delete vertex;
}

LineageGraphVertex *LineageGraph::getVertex(Cell *cell) const {
	int index = indexOfCell(cell);

	if (index >= 0)
		return _vertices.get(index);

	return nullptr;
}
Vector<LineageGraphVertex *> LineageGraph::getVertices() const { return _vertices; }

void LineageGraph::addEdge(Cell *parentCell, Cell *childCell) {
	// Check if the Cells are already in the graph
	LineageGraphVertex *parentVertex = getVertex(parentCell);
	LineageGraphVertex *childVertex = getVertex(childCell);

	if (parentVertex == nullptr) {
		// Parent Cell was not found in the graph

		// Create the parent vertex
		parentVertex = addVertex(parentCell);
	}
	if (childVertex == nullptr) {
		// Child Cell was not found in the graph

		// Create the child vertex
		childVertex = addVertex(childCell);
	}

	// Link the two vertices symmetrically
	parentVertex->linkToChild(childVertex);
	childVertex->linkToParent(parentVertex);
}
void LineageGraph::removeEdge(Cell *parentCell, Cell *childCell) {
	LineageGraphVertex *parentVertex = getVertex(parentCell);
	LineageGraphVertex *childVertex = getVertex(childCell);

	if (parentVertex)
		parentVertex->removeLinkToChild(childVertex);

	if (childVertex)
		childVertex->removeLinkToParent(parentVertex);
}

int LineageGraph::indexOfCell(Cell *keyCell) const {
	for (int i = 0; i < _vertices.size(); i++)
		if (_vertices.get(i)->getCell() == keyCell)
			return i;

	return -1;
}