extends TextureButton

func _pressed():
	var rootNode = get_tree().get_root()
	rootNode.get_node("CellSpawner/UI/FpsCounter").text = "-1" # Toggles FpsCounter off
	rootNode.get_node("CellSpawner/UI/TimeCounter").text = "-1" # Toggles TimeCounter off
	rootNode.get_node("CellSpawner/UI/MenuPanels/SaveAndQuitMenuPanel").visible = false
	rootNode.get_node("CellSpawner/UI/StatsPanel").visible = false
	rootNode.get_node("CellSpawner/UI/NavBar").visible = false
	rootNode.get_node("CellSpawner/UI/BarPanel").visible = true
	var spawner = rootNode.get_node("CellSpawner")
	for child in spawner.get_children():
		if child is Cell:
			spawner.remove_child(child)
			child.queue_free()
			
	var pauseButton = rootNode.get_node("CellSpawner/UI/NavBar/PauseButton")
	pauseButton.get_child(!get_tree().paused).visible = false # Change pause button visually
	pauseButton.get_child(get_tree().paused).visible = true
	GlobalVariables.time_scale_backup_two = Engine.time_scale # Pause and unpause
	Engine.time_scale = GlobalVariables.time_scale_backup_one
	GlobalVariables.time_scale_backup_one = GlobalVariables.time_scale_backup_two

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
