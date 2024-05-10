extends Button

var menu_panel = null
var pauseButton = null

func _pressed():
	menu_panel.visible = !menu_panel.visible

# Called when the node enters the scene tree for the first time.
func _ready():
	menu_panel = get_parent().get_parent().get_node("MenuPanel")
	process_mode = Node.PROCESS_MODE_ALWAYS

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
