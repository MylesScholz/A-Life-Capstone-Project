extends TextureButton

func _pressed():
	var rootNode = get_tree().get_root()
	rootNode.get_node("CellSpawner/UI/FpsCounter").text = "-1" # Toggles FpsCounter off
	rootNode.get_node("CellSpawner/UI/TimeCounter").text = "-1" # Toggles TimeCounter off
	rootNode.get_node("CellSpawner/UI/SpeedDisplay").call("toggle_display")
	rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = false
	rootNode.get_node("CellSpawner/UI/StatsPanel").visible = false
	rootNode.get_node("CellSpawner/UI/NavBar").visible = false
	rootNode.get_node("CellSpawner/UI/BarPanel").visible = true
	var env = rootNode.get_node("CellSpawner/CellEnvironment")
	for child in env.get_children():
		if child is Cell or child is NutrientZone:
			env.remove_child(child)
			child.queue_free()
			
	rootNode.get_node("CellSpawner/UI/NavBar/PauseButton").call("unpause") # Should already be paused but does not matter
