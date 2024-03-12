extends VBoxContainer

signal selection(cell_select)
# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS
	GlobalSignals.connect("cell_selected", Callable(self, "_on_Cell_Selected"))

	var default_label = Label.new()
	default_label.text = "Click a cell to see information"
	add_child(default_label)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_Cell_Selected(cell_instance):
	clear_stats()
	var cell = cell_instance.get_cell()

	var cell_name_label  = Label.new()
	cell_name_label.text = "Cell: " + str(cell)
	add_child(cell_name_label)
	
	var size_label  = Label.new()
	size_label.text = "Size: "
	add_child(size_label)
	
	var alive_label = Label.new()
	alive_label.text = "Alive: "
	add_child(alive_label)
	
	var age_label  = Label.new()
	age_label.text = "Age: "
	add_child(age_label)
	
	var birth_label  = Label.new()
	birth_label.text = "Birth Time: "
	add_child(birth_label)
	
	var nutrients_label  = Label.new()
	nutrients_label.text = "Nutrients: "
	add_child(nutrients_label)

func clear_stats():
	for child in get_children():
		remove_child(child)
		child.queue_free()
