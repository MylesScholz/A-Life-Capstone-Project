#pragma once

#include "lineage_graph.hpp"
#include "nutrient_zone.hpp"

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "cell_spawner.hpp"
#include "stats.hpp"

using namespace godot;

class CellEnvironment : public Area2D {
	GDCLASS(CellEnvironment, Area2D)

protected:
	static void _bind_methods();

public:
	CellEnvironment();
	~CellEnvironment();

	void spawnNutrientZone();
	void removeAllNutrientZones();

	int GetAliveCount();
	int GetNutrientZoneCount();

	void setNutrientZoneScene(const Ref<PackedScene>);
	Ref<PackedScene> getNutrientZoneScene() const;

	void setNNutrientZones(const int);
	int getNNutrientZones() const;

	void addCell(Cell *);
	void removeCell(Cell *);
	LineageGraph *getLineageGraph();

	void _on_cell_death(Cell *);

private:
	int _nNutrientZones;
	Ref<PackedScene> _nutrientZoneScene;
	LineageGraph _lineageGraph;
};