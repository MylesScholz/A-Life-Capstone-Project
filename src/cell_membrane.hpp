#pragma once

#include "cell.hpp"
#include "cell_structure.hpp"
#include "receptor.hpp"

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class CellMembrane : public CellStructure {
	GDCLASS(CellMembrane, CellStructure)

protected:
	static void _bind_methods();

public:
	CellMembrane();
	~CellMembrane();

	void activate(CellState *) override;
	void _on_receptor_activated(Receptor *);
	void _on_receptor_deactivated(Receptor *);

	Vector<Receptor *> getReceptors();
	void createReceptor();
	void removeReceptor();

	Vector<Receptor *> getActivatedReceptors();

	void _ready() override;

private:
	Vector<Receptor *> _receptors;
	Vector<Receptor *> _activatedReceptors;
};