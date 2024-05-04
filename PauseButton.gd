extends TextureButton

func _pressed():
	var rootNode = get_tree().get_root()
	var SaveAndQuit = rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible
	var SimSettings = rootNode.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible
	if (!SaveAndQuit and !SimSettings): # Cannot pause in settings
		pause_functionality()

func pause_functionality():
	get_child(!GlobalVariables.paused).visible = false # Change pause button visually
	get_child(GlobalVariables.paused).visible = true
	
	GlobalVariables.paused = !GlobalVariables.paused # Note that button was clicked
	GlobalVariables.used_pause_button = !GlobalVariables.used_pause_button
	
	GlobalVariables.time_scale_backup_two = Engine.time_scale # Save prev delta
	Engine.time_scale = GlobalVariables.time_scale_backup_one # Set delta
	GlobalVariables.time_scale_backup_one = GlobalVariables.time_scale_backup_two

func unpause(): # If paused, unpause
	if (Engine.time_scale == 0):
		pause_functionality()

func pause(): # If unpaused, pause
	if (Engine.time_scale != 0):
		pause_functionality()
