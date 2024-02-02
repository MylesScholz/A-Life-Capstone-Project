extends Button

var menu_panel = null
var pauseButton = null

func _pressed():
	menu_panel.visible = !menu_panel.visible
	var rootNode = get_tree().get_root()
	pauseButton = rootNode.get_node("CellSpawner/UI/NavBar/PauseButton")
	if (Engine.time_scale != 0):
		pauseButton.get_child(1).visible = false # Change pause button visually
		pauseButton.get_child(0).visible = true
		GlobalVariables.time_scale_backup_two = Engine.time_scale # Pause and unpause
		Engine.time_scale = GlobalVariables.time_scale_backup_one
		GlobalVariables.time_scale_backup_one = GlobalVariables.time_scale_backup_two

# Called when the node enters the scene tree for the first time.
func _ready():
	menu_panel = get_parent().get_parent().get_node("MenuPanel")
	process_mode = Node.PROCESS_MODE_ALWAYS

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
