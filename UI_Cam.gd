extends Camera2D

var tracked_cell = null
var stats_tracker = null
var default_zoom = Vector2(1, 1)
var zoom_level = Vector2(1.7, 1.7)
var cell_position = null
var cell_select_panel = null

var c_key_was_pressed = false

# Called when the node enters the scene tree for the first time.
func _ready():
	cell_select_panel = get_parent().get_node("UI/CellSelectPanel")
	stats_tracker = get_parent().get_node("UI/StatsPanel/TabContainer/Stats")
	anchor_mode = 0
	zoom = default_zoom
	set_process_input(true)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	if Input.is_action_just_pressed("camera focus") and tracked_cell :
		c_key_was_pressed = !c_key_was_pressed
		
	if c_key_was_pressed and tracked_cell :
		zoom = zoom_level
		anchor_mode = 1
		cell_position = tracked_cell.global_position
		position = cell_position
			
	else:
		zoom = default_zoom 
		anchor_mode = 0
	
	if Input.is_action_just_pressed("deselect cell") and tracked_cell :
		clear_selection()
		

func on_cell_select (cell):
	cell_select_panel.visible = true
	tracked_cell = cell  # Assume 'cell' is the node to follow

func clear_selection ():
	cell_select_panel.visible = false
	zoom = default_zoom 
	anchor_mode = 0
	cell_position = null
	stats_tracker._clear_selected_cell()
	tracked_cell = null
	
