extends TextureButton

func _pressed():
	var rootNode = get_tree().get_root()
	rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = true
	
	var pauseButton = rootNode.get_node("CellSpawner/UI/NavBar/PauseButton")
	if (!get_tree().paused):
		pauseButton.get_child(1).visible = false # Change pause button visually
		pauseButton.get_child(0).visible = true
		get_tree().paused = true # Pause and unpause

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
