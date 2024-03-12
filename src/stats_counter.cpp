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
	
	//this->connect("cell_selected", Callable(this, "_update_Stats"));

	Label* default_label = new Label();
	default_label->set_text("Click a cell to see information");
    add_child(default_label);
}

void StatsCounter::_update_Stats(Variant cell_instance){
	clear_stats();
	

	String cell = cell_instance.call("get_cell");

        // Then create and add other labels as in the script
    add_label("Cell: " + cell);
    add_label("Size: ");
}

void StatsCounter::clear_stats() {
    // Assuming all stat labels are added to a specific group for easy identification
    const String stat_label_group = "stat_labels";
    
    // Get all children nodes
    Array children = get_children();
    for (int i = 0; i < children.size(); ++i) {
        Node *child = Object::cast_to<Node>(children[i]);
        if (!child) continue; // Skip if for some reason the cast failed
        
        // Check if the child is in the 'stat_labels' group
        if (child->is_in_group(stat_label_group)) {
            // Remove the child from the scene tree
            remove_child(child);
            // Optionally, to free memory if you're not going to reuse the node
            child->queue_free();
        }
    }
}

void StatsCounter::add_label(String text) {
    Label* label = new Label();
    label->set_text(text);
    
    // Assign the label to a group for easy identification
    const String stat_label_group = "stat_labels";
    label->add_to_group(stat_label_group);
    
    // Add the label as a child of this node
    add_child(label);
}

