extends TextureButton

#var paused = false
func _pressed():
	var rootNode = get_tree().get_root()
	#paused = GlobalVariables.used_pause_button
	
	# Speed up if less than 2 while not paused
	if (Engine.time_scale < GlobalVariables.max_speed and not GlobalVariables.paused):
		Engine.time_scale *= 2
		rootNode.get_node("CellSpawner/UI/SpeedDisplay").call("update_speed_display", Engine.time_scale)
	
	# If paused, speed up to take place when unpaused
	if (Engine.time_scale == 0 and (GlobalVariables.time_scale_backup_one < GlobalVariables.max_speed)):
		GlobalVariables.time_scale_backup_one *= 2
		rootNode.get_node("CellSpawner/UI/SpeedDisplay").call("update_speed_display", GlobalVariables.time_scale_backup_one)
