extends TextureButton

func _pressed():
	var root = get_tree().get_root()
	root.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = false
	root.get_node("CellSpawner/UI/MenuPanels/SimSettingsMenuPanel").visible = true

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
