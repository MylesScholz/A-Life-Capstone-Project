#pragma once

#include "lineage_graph_vertex.hpp"

#include <godot_cpp/classes/collision_object2d.hpp>
#include <godot_cpp/templates/vector.hpp>

using namespace godot;

class LineageGraph {
public:
	LineageGraph();
	~LineageGraph();

	LineageGraphVertex *getLUCA() const;
	Vector2 getLUCAPosition();
	void updateLUCAEdges();

	Vector2 storeCell(Cell *);
	Vector2 getCellPosition(Cell *);

	LineageGraphVertex *addVertex(Cell *);
	LineageGraphVertex *addVertex(LineageGraphVertex *);
	void removeVertex(Cell *);
	void removeVertex(LineageGraphVertex *);

	LineageGraphVertex *getVertex(Cell *) const;
	Vector<LineageGraphVertex *> getVertices() const;

	void addEdge(Cell *, Cell *);
	void removeEdge(Cell *, Cell *);

	int indexOfCell(Cell *) const;

private:
	int _nColumns;
	int _storageSpacing;
	Vector2 _storageBasis;
	Vector<LineageGraphVertex *> _vertices;
	LineageGraphVertex *_LUCA;
};