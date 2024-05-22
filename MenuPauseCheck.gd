extends CheckButton

var pause_button = null
var menu_panel = null
var toggled_check = false
var current_state = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pause_button = get_parent().get_parent().get_parent().get_parent().get_node("NavBar/SpeedControlPanel/PauseButton")
	menu_panel = get_parent().get_parent().get_parent()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	var new_state = toggled_check and menu_panel.visible
	if new_state != current_state:
		current_state = new_state
		if current_state:
			pause_button.pause()
		else:
			pause_button.unpause()

func _toggled(toggled_on):
	toggled_check = toggled_on
