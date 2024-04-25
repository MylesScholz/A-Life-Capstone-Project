extends Button

var stats_panel = null

func _pressed():
	stats_panel.visible = !stats_panel.visible

# Called when the node enters the scene tree for the first time.
func _ready():
	stats_panel = get_parent().get_parent().get_node("StatsPanel")
	process_mode = Node.PROCESS_MODE_ALWAYS


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
