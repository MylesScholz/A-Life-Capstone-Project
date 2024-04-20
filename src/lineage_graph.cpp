#include "lineage_graph.hpp"

LineageGraph::LineageGraph() {
	_vertices = Vector<LineageGraphVertex *>();
}
LineageGraph::~LineageGraph() {}

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