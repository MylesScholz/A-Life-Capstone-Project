extends TextureButton

func _pressed():
	var menuPanels = get_parent().get_parent().get_parent().get_parent().get_parent()
	menuPanels.get_node("MenuPanels/SaveAndQuitMenuPanel").visible = true
	menuPanels.get_node("MenuPanels/SimSettingsMenuPanel").visible = false

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
