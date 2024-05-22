extends Button

var menu_panel = null
var bar_panel = null
var menu_exit = null

func _pressed():
	menu_panel.visible = !menu_panel.visible
	bar_panel.visible = false
	menu_exit.from_main_menu = true

# Called when the node enters the scene tree for the first time.
func _ready():
	menu_panel = get_parent().get_parent().get_parent().get_node("MenuPanel")
	menu_exit = menu_panel.get_node("ExitMenuButton")
	bar_panel = get_parent().get_parent()
	process_mode = Node.PROCESS_MODE_ALWAYS


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
