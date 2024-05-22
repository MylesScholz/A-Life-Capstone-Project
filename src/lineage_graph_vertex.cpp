#include "lineage_graph_vertex.hpp"

LineageGraphVertex::LineageGraphVertex(Cell *cell) {
	_cell = cell;
	_parents = Vector<LineageGraphVertex *>();
	_children = Vector<LineageGraphVertex *>();
}
LineageGraphVertex::~LineageGraphVertex() {}

void LineageGraphVertex::setCell(Cell *cell) { _cell = cell; }
Cell *LineageGraphVertex::getCell() const { return _cell; }

int LineageGraphVertex::getIndegree() const { return _parents.size(); }
int LineageGraphVertex::getOutdegree() const { return _children.size(); }
int LineageGraphVertex::getDegreeSum() const { return _parents.size() + _children.size(); }

void LineageGraphVertex::linkToParent(LineageGraphVertex *parent) {
	if (_parents.find(parent) == -1)
		_parents.push_back(parent);
}
void LineageGraphVertex::removeLinkToParent(LineageGraphVertex *parent) {
	int index = _parents.find(parent);

	if (index >= 0)
		_parents.remove_at(index);
}

LineageGraphVertex *LineageGraphVertex::getParent(Cell *parent) const {
	int index = indexOfParent(parent);

	if (index >= 0)
		return _parents.get(index);

	return nullptr;
}
Vector<LineageGraphVertex *> LineageGraphVertex::getParents() const { return _parents; }

int LineageGraphVertex::indexOfParent(Cell *keyCell) const {
	for (int i = 0; i < _parents.size(); i++)
		if (_parents.get(i)->getCell() == keyCell)
			return i;

	return -1;
}
int LineageGraphVertex::indexOfParent(LineageGraphVertex *keyVertex) const {
	for (int i = 0; i < _parents.size(); i++)
		if (_parents.get(i) == keyVertex)
			return i;

	return -1;
}

void LineageGraphVertex::linkToChild(LineageGraphVertex *child) {
	if (_children.find(child) == -1)
		_children.push_back(child);
}
void LineageGraphVertex::removeLinkToChild(LineageGraphVertex *child) {
	int index = _children.find(child);

	if (index >= 0)
		_children.remove_at(index);
}

LineageGraphVertex *LineageGraphVertex::getChild(Cell *child) const {
	int index = indexOfChild(child);

	if (index >= 0)
		return _children.get(index);

	return nullptr;
}
Vector<LineageGraphVertex *> LineageGraphVertex::getChildren() const { return _children; }

int LineageGraphVertex::indexOfChild(Cell *keyCell) const {
	for (int i = 0; i < _children.size(); i++)
		if (_children.get(i)->getCell() == keyCell)
			return i;

	return -1;
}
int LineageGraphVertex::indexOfChild(LineageGraphVertex *keyVertex) const {
	for (int i = 0; i < _children.size(); i++)
		if (_children.get(i) == keyVertex)
			return i;

	return -1;
}