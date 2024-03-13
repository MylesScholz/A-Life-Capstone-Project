#include "stats_counter.hpp"
#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

#include "helpers.hpp"

using namespace godot;

void StatsCounter::_bind_methods() {
	ADD_SIGNAL(MethodInfo("cell_selected", PropertyInfo(Variant::OBJECT, "cell")));
}

StatsCounter::StatsCounter() {}
StatsCounter::~StatsCounter() {}

void StatsCounter::_process(double delta) {
	DONT_RUN_IN_EDITOR;
}

void StatsCounter::_ready() {
	set_process_mode(Node::PROCESS_MODE_ALWAYS);

    Cell* selected_cell = nullptr;

    add_label("Click a cell to see information");
}

void StatsCounter::_update_Stats(Variant cell_instance){
    
    
    selected_cell = Object::cast_to<Cell>(cell_instance);
    if (selected_cell) {
        clear_stats();
        Array stats = cell_instance.call("getStats");
        add_label("Birth Time: " + String(stats[0]));
        add_label("Alive: " + String(stats[1]));
        add_label("Age: " + String(stats[2])); 
        add_label("Energy: " + String(stats[3]));
        add_label("Nutrients: " + String(stats[4]));
    }
}

void StatsCounter::clear_stats() {
    
    Array children = get_children();
    for (int i = 0; i < children.size(); ++i) {
        Label* child = Object::cast_to<Label>(children[i]);
        // Check if the cast was successful
        if (child) {
            remove_child(child);
            // Optionally, queue the child for deletion
            child->queue_free();
        }
    }
}

void StatsCounter::add_label(String text) {
    Label* label = new Label();
    label->set_text(text);
    add_child(label);
}
