extends CheckButton

var pause_button = null
var menu_panel = null
var enabled = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pause_button = get_parent().get_parent().get_parent().get_parent().get_node("NavBar/SpeedControlPanel/PauseButton")
	menu_panel = get_parent().get_parent().get_parent()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if enabled and menu_panel.visible:
		pause_button.pause()

func _toggled(toggled_on):
	enabled = toggled_on
