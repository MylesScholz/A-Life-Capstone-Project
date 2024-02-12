#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/viewport.hpp>

namespace godot {

class CellSpawner : public Node {
	GDCLASS(CellSpawner, Node)

protected:
	static void _bind_methods();

public:
	CellSpawner();
	~CellSpawner();

	void setNumCells(const int);
	int getNumCells() const;

	void setCellScene(const Ref<PackedScene>);
	Ref<PackedScene> getCellScene() const;

	void setMinForce(const float);
	float getMinForce() const;

	void setMaxForce(const float);
	float getMaxForce() const;

	void spawnCell(bool isImmortal = 0);

	void removeAllCells();

	void _ready() override;

private:
	Ref<PackedScene> _cellScene;
	Ref<RandomNumberGenerator> rand;
	int _numCells = 1;
	float _minForce = 50.0;
	float _maxForce = 150.0;
};

} // namespace godot