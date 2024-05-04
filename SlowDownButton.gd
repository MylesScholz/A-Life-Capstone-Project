extends TextureButton

var paused
func _pressed():
	var rootNode = get_tree().get_root()
	
	# Slow down if geater than .5 while not paused
	if (Engine.time_scale > GlobalVariables.min_speed):
		Engine.time_scale /= 2
		rootNode.get_node("CellSpawner/UI/SpeedDisplay").call("update_speed_display", Engine.time_scale)
	
	# If paused, slow down to take place when unpaused
	if (Engine.time_scale == 0 and (GlobalVariables.time_scale_backup_one > GlobalVariables.min_speed)):
		GlobalVariables.time_scale_backup_one /= 2
		rootNode.get_node("CellSpawner/UI/SpeedDisplay").call("update_speed_display", GlobalVariables.time_scale_backup_one)
