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
	void modify(String, float) override;
	void applyScale(const float) override;

	void _on_receptor_activated(Receptor *);
	void _on_receptor_deactivated(Receptor *);

	void setNReceptors(const int);
	int getNReceptors() const;

	Vector<Receptor *> getReceptors();
	Vector<Receptor *> getActivatedReceptors();

	void _ready() override;

private:
	void _rearrangeReceptors();

	void _createReceptor();
	void _createReceptors(const int);
	void _removeReceptor();
	void _removeReceptors(const int);

	void _updateReceptors();

	int _nReceptors;
	Vector<Receptor *> _receptors;
	Vector<Receptor *> _activatedReceptors;
};