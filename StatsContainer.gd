extends VBoxContainer


# Called when the node enters the scene tree for the first time.
func _ready():
	update_stats()
	process_mode = Node.PROCESS_MODE_ALWAYS


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	

func update_stats():
	var cell_spawner = get_node("/root/CellSpawner")
	var num_cells = cell_spawner.call("get_num_cells")
	
	clear_stats()
	
	var label = Label.new()
	label.text = "Total Cell Count: " + str(num_cells)
	add_child(label)

func clear_stats():
	for child in get_children():
		remove_child(child)
		child.queue_free()
