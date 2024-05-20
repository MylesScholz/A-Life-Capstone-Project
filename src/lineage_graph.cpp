#include "lineage_graph.hpp"

LineageGraph::LineageGraph() {
	// Number of columns of Cells in the storage area
	_nColumns = 5;
	// Storage basis vector; the top left position of the storage area; just to the right of the CellEnvironment
	_storageBasis = Vector2(1400, 0);
	// Spacing between Cells in the storage area
	_storageSpacing = 200;
	_vertices = Vector<LineageGraphVertex *>();
	// Last universal common ancestor
	_LUCA = new LineageGraphVertex(nullptr);
}
LineageGraph::~LineageGraph() {
	for (LineageGraphVertex *vertex : _vertices)
		delete vertex;
}

LineageGraphVertex *LineageGraph::getLUCA() const { return _LUCA; }
Vector2 LineageGraph::getLUCAPosition() {
	return _storageBasis + Vector2(0, _storageSpacing);
}
void LineageGraph::updateLUCAEdges() {
	if (!_LUCA)
		return;

	for (LineageGraphVertex *vertex : _vertices) {
		Vector<LineageGraphVertex *> parents = vertex->getParents();
		if (parents.size() == 0) {
			vertex->linkToParent(_LUCA);
			_LUCA->linkToChild(vertex);
		} else if (parents.size() > 1 && parents.find(_LUCA) >= 0) {
			vertex->removeLinkToParent(_LUCA);
			_LUCA->removeLinkToChild(vertex);
		}
	}
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
Vector2 LineageGraph::getCellPosition(Cell *cell) {
	// Initialize position at the storage basis vector
	Vector2 position = _storageBasis;

	int index = indexOfCell(cell);
	if (index < 0)
		return Vector2();

	position.x += (index % _nColumns) * _storageSpacing;
	position.y += (index / _nColumns) * _storageSpacing;

	return position;
}

LineageGraphVertex *LineageGraph::addVertex(Cell *cell) {
	LineageGraphVertex *newVertex = new LineageGraphVertex(cell);

	_vertices.push_back(newVertex);

	updateLUCAEdges();
	return newVertex;
}
LineageGraphVertex *LineageGraph::addVertex(LineageGraphVertex *vertex) {
	if (_vertices.find(vertex) == -1)
		_vertices.push_back(vertex);

	updateLUCAEdges();
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

	updateLUCAEdges();
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

	updateLUCAEdges();
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

	updateLUCAEdges();
}
void LineageGraph::removeEdge(Cell *parentCell, Cell *childCell) {
	LineageGraphVertex *parentVertex = getVertex(parentCell);
	LineageGraphVertex *childVertex = getVertex(childCell);

	if (parentVertex)
		parentVertex->removeLinkToChild(childVertex);

	if (childVertex)
		childVertex->removeLinkToParent(parentVertex);

	updateLUCAEdges();
}

int LineageGraph::indexOfCell(Cell *keyCell) const {
	for (int i = 0; i < _vertices.size(); i++)
		if (_vertices.get(i)->getCell() == keyCell)
			return i;

	return -1;
}