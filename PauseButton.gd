extends TextureButton

# Needs a way for c++ scripts to still run when paused for
# things like the fps counter, main menu and reset buttons
var main_menu =  null

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
		_pressed()
		get_child(0).visible = false # Change pause button to unpaused
		get_child(1).visible = true

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS
	main_menu = get_parent()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
