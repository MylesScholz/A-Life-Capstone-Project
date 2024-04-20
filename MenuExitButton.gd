extends TextureButton

# Should not be able to unpause when in menu

func _pressed():
	var rootNode = get_tree().get_root()
	rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = false
	rootNode.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible = false
	
	if (!GlobalVariables.used_pause_button):
		print("unpausing")
		var pauseButton = rootNode.get_node("CellSpawner/UI/NavBar/PauseButton")
		pauseButton.get_child(GlobalVariables.used_pause_button).visible = false # Change pause button visually
		pauseButton.get_child(!GlobalVariables.used_pause_button).visible = true
		GlobalVariables.time_scale_backup_two = Engine.time_scale # Pause and unpause
		Engine.time_scale = GlobalVariables.time_scale_backup_one
		GlobalVariables.time_scale_backup_one = GlobalVariables.time_scale_backup_two

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
