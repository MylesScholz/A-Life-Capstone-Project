#include "register_types.hpp"

#include "cell.hpp"
#include "cell_spawner.hpp"
#include "cell_state.hpp"
#include "flagella.hpp"
#include "fps_counter.hpp"
#include "mitochondria.hpp"
#include "nucleus.hpp"
#include "ribosomes.hpp"
#include "start_button.hpp"
#include "stats_counter.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_gdextension_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<StatsCounter>();
	ClassDB::register_class<FpsCounter>();
	ClassDB::register_class<StartButton>();
	ClassDB::register_class<CellSpawner>();
	ClassDB::register_class<Cell>();
	ClassDB::register_class<CellState>();
	ClassDB::register_class<CellStructure>();
	ClassDB::register_class<Nucleus>();
	ClassDB::register_class<Mitochondria>();
	ClassDB::register_class<Ribosomes>();
	ClassDB::register_class<Flagella>();
}

void uninitialize_gdextension_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT
library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
		const GDExtensionClassLibraryPtr p_library,
		GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
			r_initialization);

	init_obj.register_initializer(initialize_gdextension_module);
	init_obj.register_terminator(uninitialize_gdextension_module);
	init_obj.set_minimum_library_initialization_level(
			MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
