extends Button
var rootNode = null

func _pressed():
	ui_reset()

# Called when the node enters the scene tree for the first time.
func _ready():
	rootNode = get_tree().get_root()
	process_mode = Node.PROCESS_MODE_ALWAYS

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass

func ui_reset():
	rootNode.get_node("CellSpawner/UI/ExtraPanel/FpsCounter").text = "-1" # Toggles FpsCounter off
	rootNode.get_node("CellSpawner/UI/ExtraPanel/TimeCounter").text = "-1" # Toggles TimeCounter off
	rootNode.get_node("CellSpawner/UI/MenuPanel").visible = false
	rootNode.get_node("CellSpawner/UI/StatsPanel").visible = false
	rootNode.get_node("CellSpawner/UI/NavBar").visible = false
	rootNode.get_node("CellSpawner/UI/BarPanel").visible = true
	rootNode.get_node("CellSpawner/UI/CellSelectPanel").visible = false
	rootNode.get_node("CellSpawner/UI/ExtraPanel").visible = false
	
	rootNode.get_node("CellSpawner/UI/StatsPanel/TabContainer/Stats")._clear_selected_cell() # clear any selections
	
	var spawner = rootNode.get_node("CellSpawner")
	for child in spawner.get_children():
		if child is Cell:
			spawner.remove_child(child)
			child.queue_free()
	
	for i in range(spawner.get_num_cells()):
		spawner.spawn_cell(1)
