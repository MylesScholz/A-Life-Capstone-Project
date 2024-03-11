extends TextureButton

# Should not be able to unpause when in menu

func _pressed():
	var rootNode = get_tree().get_root()
	rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = false
	rootNode.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible = false
	
	if (!GlobalVariables.used_pause_button):
		var pauseButton = rootNode.get_node("CellSpawner/UI/NavBar/PauseButton")
		pauseButton.get_child(!get_tree().paused).visible = false # Change pause button visually
		pauseButton.get_child(get_tree().paused).visible = true
		get_tree().paused = !get_tree().paused # Pause and unpause

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
