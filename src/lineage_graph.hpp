#pragma once

#include "lineage_graph_vertex.hpp"

#include <godot_cpp/templates/vector.hpp>

using namespace godot;

class LineageGraph {
public:
	LineageGraph();
	~LineageGraph();

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
	Vector<LineageGraphVertex *> _vertices;
};