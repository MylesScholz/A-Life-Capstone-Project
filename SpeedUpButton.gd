extends TextureButton


func _pressed():
	if (Engine.time_scale == 0): # If paused, unpause
		var rootNode = get_tree().get_root()
		rootNode.get_node("CellSpawner/UI/NavBar/PauseButton").call("_pressed")
	
	# Always speed up	
	Engine.time_scale += 0.25
	print("delta = ", Engine.time_scale)
	GlobalVariables.paused_by_speed = false
