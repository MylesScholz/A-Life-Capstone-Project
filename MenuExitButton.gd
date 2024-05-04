extends TextureButton

# Should not be able to unpause when in menu

func _pressed():
	var rootNode = get_tree().get_root()
	rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = false
	rootNode.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible = false
	
	if (!GlobalVariables.used_pause_button):
		var pauseButton = rootNode.get_node("CellSpawner/UI/NavBar/PauseButton")
		pauseButton.call("unpause")


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
