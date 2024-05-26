#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/spin_box.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "cell.hpp"

using namespace godot;

class CellSpawner : public Node {
	GDCLASS(CellSpawner, Node)

protected:
	static void _bind_methods();

public:
	CellSpawner();
	~CellSpawner();

	void setNumCells(const int);
	int getNumCells() const;

	int GetAliveCount();

	void setCellScene(const Ref<PackedScene>);
	Ref<PackedScene> getCellScene() const;

	void setMinForce(const float);
	float getMinForce() const;

	void setMaxForce(const float);
	float getMaxForce() const;

	void setResourceProportion(const float);
	float getResourceProportion() const;

	void spawnCell(bool isImmortal = 0);

	void removeAllCells();

	void _ready() override;
	void _on_cell_reproduction(Cell *);

private:
	Ref<PackedScene> _cellScene;
	int _numCells = 1;
	float _minForce = 50.0;
	float _maxForce = 150.0;
	float _resourceProportion = 0.75;
};