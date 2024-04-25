extends TextureButton


func _pressed():
	if (Engine.time_scale - 0.25 > 0): # Cannot have a negative delta value
		Engine.time_scale -= 0.25
		print("delta = ", Engine.time_scale)
		
	elif (Engine.time_scale > 0): # If trying to become negative, pause
		var rootNode = get_tree().get_root()
		rootNode.get_node("CellSpawner/UI/NavBar/PauseButton").call("_pressed")
		GlobalVariables.paused_by_speed = true
		
	elif (!GlobalVariables.paused_by_speed): # If paused by the pause button start simulation and slow down
		var rootNode = get_tree().get_root()
		rootNode.get_node("CellSpawner/UI/NavBar/PauseButton").call("_pressed")
		Engine.time_scale -= 0.25
		print("delta = ", Engine.time_scale)
