extends TextureButton

func _pressed():
	var rootNode = get_tree().get_root()
	rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = true
	
	var pauseButton = rootNode.get_node("CellSpawner/UI/NavBar/PauseButton")
	if (Engine.time_scale != 0):
		pauseButton.call("pause")
		GlobalVariables.used_pause_button = false
