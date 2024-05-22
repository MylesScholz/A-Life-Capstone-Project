extends VBoxContainer

var cell_spawner
var cell_zone
var cell_stats
var ui_cam
var base_label

# Called when the node enters the scene tree for the first time.
func _ready():
	ui_cam = get_node("/root/CellSpawner/UI_Cam")
	base_label = get_node("BaseLabel")
	
	clear_stats()
	
	var timer = Timer.new()
	timer.wait_time = 0.25  # Call update_stats every second
	timer.autostart = true
	timer.one_shot = false  # Make the timer repeat
	add_child(timer)
	timer.connect("timeout", Callable(self, "update_stats"))


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func update_stats():
	# if a cell is selected
	if ui_cam.tracked_cell:
		var stats_array = ui_cam.tracked_cell.getStats() # get prepackaged stats array
		var index = 0
		show_stats()
		for child in self.get_children(): #get current labels in child
			if index >= stats_array.size():
				break
				
			if child is Label:
				var label_prefix = child.text.split(":")[0] + ": " # get content after semicolons, append to end
				child.text = label_prefix + str(stats_array[index])
				index += 1 # only increment on hit
			elif child is HSplitContainer:
				var progress_bar = child.get_child(1)
				if progress_bar is ProgressBar:
					progress_bar.value = float(stats_array[index])
					index += 1 # only increment on hit

func clear_stats():
	for child in self.get_children():
		if child is Label or child is HSplitContainer:
			child.visible=false
	
	base_label.visible=true

func show_stats():
	for child in self.get_children():
		if child is Label or child is HSplitContainer:
			child.visible=true
	
	base_label.visible=false
