#pragma once

#include "cell.hpp"

#include <godot_cpp/templates/vector.hpp>

using namespace godot;

class LineageGraphVertex {
public:
	LineageGraphVertex(Cell *);
	~LineageGraphVertex();

	void setCell(Cell *);
	Cell *getCell() const;

	int getIndegree() const;
	int getOutdegree() const;
	int getDegreeSum() const;

	void linkToParent(LineageGraphVertex *);
	void removeLinkToParent(LineageGraphVertex *);

	LineageGraphVertex *getParent(Cell *) const;
	Vector<LineageGraphVertex *> getParents() const;

	int indexOfParent(Cell *) const;
	int indexOfParent(LineageGraphVertex *) const;

	void linkToChild(LineageGraphVertex *);
	void removeLinkToChild(LineageGraphVertex *);

	LineageGraphVertex *getChild(Cell *) const;
	Vector<LineageGraphVertex *> getChildren() const;

	int indexOfChild(Cell *) const;
	int indexOfChild(LineageGraphVertex *) const;

private:
	Cell *_cell;
	Vector<LineageGraphVertex *> _parents;
	Vector<LineageGraphVertex *> _children;
};