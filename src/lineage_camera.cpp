#include "lineage_camera.hpp"

void LineageCamera::_bind_methods() {
	ClassDB::bind_method(D_METHOD("select_cell", "cell"), &LineageCamera::selectCell);
	ClassDB::bind_method(D_METHOD("select_luca"), &LineageCamera::selectLUCA);
}

LineageCamera::LineageCamera() {}
LineageCamera::~LineageCamera() {}

void LineageCamera::selectCell(Cell *cell) {
	_selectCellPrompt->set_visible(false);
	_LUCAMessage->set_visible(false);
	clearButtonContainers();

	if (!cell->get_node<CellState>("CellState")->getAlive()) {
		_subViewportContainer->set_visible(true);
		this->set_global_position(cell->get_global_position());
	} else {
		_subViewportContainer->set_visible(true);

		CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));
		CellEnvironment *cellEnvironment = spawner->get_node<CellEnvironment>("CellEnvironment");
		LineageGraph *lineageGraph = cellEnvironment->getLineageGraph();
		this->set_global_position(lineageGraph->getCellPosition(cell));
	}
	fillButtonContainers(cell);
}
void LineageCamera::selectLUCA() {
	_subViewportContainer->set_visible(false);
	_selectCellPrompt->set_visible(false);
	_LUCAMessage->set_visible(true);
	clearButtonContainers();

	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));
	CellEnvironment *cellEnvironment = spawner->get_node<CellEnvironment>("CellEnvironment");
	LineageGraph *lineageGraph = cellEnvironment->getLineageGraph();

	this->set_global_position(lineageGraph->getLUCAPosition());

	for (LineageGraphVertex *child : lineageGraph->getLUCA()->getChildren()) {
		Ref<PackedScene> buttonScene = ResourceLoader::get_singleton()->load("res://lineage_button.tscn");
		TextureButton *button = Object::cast_to<TextureButton>(buttonScene->instantiate());

		_childButtonContainer->add_child(button);
		button->call("set_cell", child->getCell(), false);
	}
}
void LineageCamera::deselect() {
	_subViewportContainer->set_visible(false);
	_selectCellPrompt->set_visible(true);
	_LUCAMessage->set_visible(false);

	clearButtonContainers();
	this->set_global_position(Vector2(0, 0));
}

void LineageCamera::fillButtonContainers(Cell *cell) {
	CellSpawner *spawner = Object::cast_to<CellSpawner>(this->find_parent("CellSpawner"));
	CellEnvironment *cellEnvironment = spawner->get_node<CellEnvironment>("CellEnvironment");
	LineageGraph *lineageGraph = cellEnvironment->getLineageGraph();

	LineageGraphVertex *cellVertex = lineageGraph->getVertex(cell);
	Vector<LineageGraphVertex *> cellParents = cellVertex->getParents();
	Vector<LineageGraphVertex *> cellChildren = cellVertex->getChildren();

	for (LineageGraphVertex *parent : cellParents) {
		Ref<PackedScene> buttonScene = ResourceLoader::get_singleton()->load("res://lineage_button.tscn");
		TextureButton *button = Object::cast_to<TextureButton>(buttonScene->instantiate());

		_parentButtonContainer->add_child(button);
		button->call("set_cell", parent->getCell(), parent == lineageGraph->getLUCA());
	}
	for (LineageGraphVertex *child : cellChildren) {
		Ref<PackedScene> buttonScene = ResourceLoader::get_singleton()->load("res://lineage_button.tscn");
		TextureButton *button = Object::cast_to<TextureButton>(buttonScene->instantiate());

		_childButtonContainer->add_child(button);
		button->call("set_cell", child->getCell(), false);
	}
}
void LineageCamera::clearButtonContainers() {
	for (int i = _parentButtonContainer->get_child_count(); i > 0; i--) {
		Node *button = _parentButtonContainer->get_child(i);
		_parentButtonContainer->remove_child(button);
	}
	for (int i = _childButtonContainer->get_child_count(); i > 0; i--) {
		Node *button = _childButtonContainer->get_child(i);
		_childButtonContainer->remove_child(button);
	}
}

void LineageCamera::_ready() {
	_subViewportContainer = Object::cast_to<SubViewportContainer>(this->find_parent("SubViewportContainer"));
	_subViewportContainer->set_visible(false);

	VBoxContainer *lineageTab = Object::cast_to<VBoxContainer>(this->find_parent("Lineage"));
	_parentButtonContainer = lineageTab->get_node<HFlowContainer>("ParentButtonContainer");
	_childButtonContainer = lineageTab->get_node<HFlowContainer>("ChildButtonContainer");
	_selectCellPrompt = lineageTab->get_node<Label>("SelectCellPrompt");
	_LUCAMessage = lineageTab->get_node<Label>("LUCAMessage");

	_selectCellPrompt->set_visible(true);
	_LUCAMessage->set_visible(false);
}