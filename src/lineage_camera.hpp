#pragma once

#include "cell_environment.hpp"
#include "lineage_graph.hpp"

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/h_flow_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/sub_viewport_container.hpp>
#include <godot_cpp/classes/texture_button.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class LineageCamera : public Camera2D {
	GDCLASS(LineageCamera, Camera2D)

protected:
	static void _bind_methods();

public:
	LineageCamera();
	~LineageCamera();

	void selectCell(Cell *);
	void selectLUCA();
	void deselect();

	void fillButtonContainers(Cell *);
	void clearButtonContainers();

	void _ready() override;

private:
	Label *_selectCellPrompt;
	Label *_LUCAMessage;
	SubViewportContainer *_subViewportContainer;
	HFlowContainer *_parentButtonContainer;
	HFlowContainer *_childButtonContainer;
};