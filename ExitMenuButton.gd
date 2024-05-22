extends Button

var menu_panel = null
var pause_button = null
var bar_panel = null
var from_main_menu = false

var pauseCheck = false

func _pressed():
	menu_panel.visible = false
	if from_main_menu:
		bar_panel.visible = true
		from_main_menu = false
	
	if pauseCheck == true:
		pause_button.unpause()

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS
	menu_panel = get_parent()
	bar_panel = get_parent().get_parent().get_node("BarPanel")
	pause_button = get_parent().get_parent().get_node("NavBar/SpeedControlPanel/PauseButton")
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass


func _on_menu_pause_check_toggled(toggled_on):
	pauseCheck = toggled_on
