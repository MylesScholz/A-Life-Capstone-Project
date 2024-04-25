extends VBoxContainer

var cell_spawner
var count_label = Label.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	cell_spawner = get_node("/root/CellSpawner")
	
	var timer = Timer.new()
	timer.wait_time = 1.0  # Call update_stats every second
	timer.autostart = true
	timer.one_shot = false  # Make the timer repeat
	add_child(timer)
	timer.connect("timeout", Callable(self, "update_stats"))
	
	#	labels
	add_child(count_label)



# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass


func update_stats():
	var cell_count = cell_spawner.get_num_cells()
	count_label.text = "Total Cells: %s" % str(cell_count)
