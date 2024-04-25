extends Button

var menu_panel = null
var pause_button = null
var bar_panel = null
var from_main_menu = false

func _pressed():
	menu_panel.visible = false
	if from_main_menu:
		bar_panel.visible = true
		from_main_menu = false

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS
	menu_panel = get_parent()
	bar_panel = get_parent().get_parent().get_node("BarPanel")
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
