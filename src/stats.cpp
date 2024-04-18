#include "stats.hpp"
#include "cell.hpp"

#include <godot_cpp/core/class_db.hpp>

#include "helpers.hpp"

using namespace godot;

void Stats::_bind_methods() {
	ADD_SIGNAL(MethodInfo("cell_selected", PropertyInfo(Variant::OBJECT, "cell")));
}

Stats::Stats() {}
Stats::~Stats() {}

void Stats::_process(double delta) {
	DONT_RUN_IN_EDITOR;

    // THIS WILL PROC IT ONCE. USE THE COMMENTED OUT BLOCK DOWN BELOW TO PROC IN CONTINUAL PROCESS
    /* 
    if (selected_cell && !has_swapped){

        has_swapped = true;
        _update_Stats(selected_cell);
    }
    */

    update_counter ++;
    if (update_counter >= 500) {
        update_counter = 0;
        if (selected_cell) { // Update every 10 frames
            _update_Stats(selected_cell);
        }
    }
}

void Stats::_ready() {
	set_process_mode(Node::PROCESS_MODE_ALWAYS);
    add_label("InstructionLabel", "Click a cell to see information");
}

void Stats::_update_Stats(Variant cell_instance){
    
    selected_cell = Object::cast_to<Cell>(cell_instance);
    if (selected_cell) {
        clear_stats();
        Array stats = cell_instance.call("getStats");
        add_label("StatLabel_1", " Birth Time: " + String(stats[0]));
        add_label("StatLabel_2", " Alive: " + String(stats[1]));
        add_label("StatLabel_3", " Age: " + String(stats[2])); 
        add_label("StatLabel_4", " Energy: " + String(stats[3]));
        add_label("StatLabel_5", " Nutrients: " + String(stats[4]));
        add_label("StatLabel_6", " Mass: " + String(stats[5]) + " µg");
        add_label("StatLabel_7", " Size: " + String(stats[6]) + " µm");
    }
}

void Stats::clear_stats() {
    
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

void Stats::add_label(String name, String text) {
    Label* label = new Label();
    label->set_name(name);
    label->set_text(text);
    add_child(label);
}