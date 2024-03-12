extends TextureButton

func _pressed():
	var root = get_tree().get_root()
	root.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = true
	root.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible = false

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
