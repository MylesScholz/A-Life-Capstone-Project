extends TextureButton

# Needs a way for c++ scripts to still run when paused for
# things like the fps counter, main menu and reset buttons

func _pressed():
	var rootNode = get_tree().get_root()
	var SaveAndQuit = rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible
	var SimSettings = rootNode.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible
	if (!SaveAndQuit and !SimSettings):
		get_child(!get_tree().paused).visible = false # Change pause button visually
		get_child(get_tree().paused).visible = true
		get_tree().paused = !get_tree().paused # Pause and unpause
		GlobalVariables.used_pause_button = !GlobalVariables.used_pause_button

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
