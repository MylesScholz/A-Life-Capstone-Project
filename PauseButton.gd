extends TextureButton

# Needs a way for c++ scripts to still run when paused for
# things like the fps counter, main menu and reset buttons
#var time_scale_backup_one: float
#var time_scale_backup_two: float
func _pressed():
	var rootNode = get_tree().get_root()
	var SaveAndQuit = rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible
	var SimSettings = rootNode.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible
	if (!SaveAndQuit and !SimSettings):
		get_child(!GlobalVariables.used_pause_button).visible = false # Change pause button visually
		get_child(GlobalVariables.used_pause_button).visible = true
		GlobalVariables.used_pause_button = !GlobalVariables.used_pause_button
		GlobalVariables.time_scale_backup_two = Engine.time_scale
		Engine.time_scale = GlobalVariables.time_scale_backup_one
		GlobalVariables.time_scale_backup_one = GlobalVariables.time_scale_backup_two

func getUsedPauseButton():
	return GlobalVariables.used_pause_button

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS
	#$time_scale_backup = $time_scale
	#$time_scale = 0
	#$time_scale = $time_scale_backup
	#time_scale_backup_one = 0

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
