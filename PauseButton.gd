extends TextureButton

func _pressed():
	var rootNode = get_tree().get_root()
	var SaveAndQuit = rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible
	var SimSettings = rootNode.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible
	if (!SaveAndQuit and !SimSettings):
		get_child(!GlobalVariables.used_pause_button).visible = false # Change pause button visually
		get_child(GlobalVariables.used_pause_button).visible = true
		
		GlobalVariables.used_pause_button = !GlobalVariables.used_pause_button # Note that button was clicked
		GlobalVariables.paused_by_speed = false # If clicked couldnt have been paused via slowing down
		
		GlobalVariables.time_scale_backup_two = Engine.time_scale # Save prev delta
		Engine.time_scale = GlobalVariables.time_scale_backup_one # Set delta
		GlobalVariables.time_scale_backup_one = GlobalVariables.time_scale_backup_two
		print("delta = ", Engine.time_scale, " pausing")

func unpause(): # If paused, unpause
	if (Engine.time_scale == 0):
		_pressed()
		get_child(0).visible = false # Change pause button to unpaused
		get_child(1).visible = true

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
