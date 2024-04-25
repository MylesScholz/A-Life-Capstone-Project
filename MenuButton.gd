extends TextureButton

func _pressed():
	var rootNode = get_tree().get_root()
	rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = true
	
	var pauseButton = rootNode.get_node("CellSpawner/UI/NavBar/PauseButton")
	if (Engine.time_scale != 0):
		pauseButton.get_child(1).visible = false # Change pause button visually
		pauseButton.get_child(0).visible = true
		GlobalVariables.time_scale_backup_two = Engine.time_scale # Pause and unpause
		Engine.time_scale = GlobalVariables.time_scale_backup_one
		GlobalVariables.time_scale_backup_one = GlobalVariables.time_scale_backup_two

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
