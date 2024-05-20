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
	rootNode = get_tree().get_root()
	
	rootNode.get_node("CellSpawner/UI/ExtraPanel/FpsCounter").text = "-1" # Toggles FpsCounter off
	rootNode.get_node("CellSpawner/UI/ExtraPanel/TimeCounter").text = "-1" # Toggles TimeCounter off
	rootNode.get_node("CellSpawner/UI/MenuPanel").visible = false
	rootNode.get_node("CellSpawner/UI/StatsPanel").visible = false
	rootNode.get_node("CellSpawner/UI/NavBar").visible = false
	rootNode.get_node("CellSpawner/UI/BarPanel").visible = true
	rootNode.get_node("CellSpawner/UI/CellSelectPanel").visible = false
	rootNode.get_node("CellSpawner/UI/ExtraPanel").visible = false
	
	
	var speed_display = rootNode.get_node("CellSpawner/UI/ExtraPanel/SpeedDisplay")
	speed_display.toggle_display()
	
	var cell_cam = rootNode.get_node("CellSpawner/UI_Cam") # clear any selections
	cell_cam.clear_selection()
	
	var spawner = rootNode.get_node("CellSpawner")
	var zones = rootNode.get_node("CellSpawner/CellEnvironment")
	
	spawner.remove_all_cells()
	
	for i in range(spawner.get_num_cells()):
		spawner.spawn_cell(1)
	
	zones.remove_all_nutrient_zones()
	
	for i in range(zones.get_n_nutrient_zones()):
		zones.spawn_nutrient_zone()
