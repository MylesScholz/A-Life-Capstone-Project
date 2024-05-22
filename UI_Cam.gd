extends Camera2D

var tracked_cell = null
var default_zoom = Vector2(1, 1)
var zoom_level = Vector2(1.7, 1.7)
var cell_position = null
var cell_select_panel = null
var cell_stats = null

var c_key_was_pressed = false
var cam_focus_check = true

# Called when the node enters the scene tree for the first time.
func _ready():
	cell_select_panel = get_parent().get_node("UI/CellSelectPanel")
	cell_stats = get_parent().get_node("UI/StatsPanel/TabContainer/Cell")
	anchor_mode = 0
	zoom = default_zoom
	set_process_input(true)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	if Input.is_action_just_pressed("camera focus") and tracked_cell :
		c_key_was_pressed = !c_key_was_pressed
	
	if c_key_was_pressed:
		camera_zoom()
	
	if !c_key_was_pressed:
		camera_unzoom()
	
	if Input.is_action_just_pressed("deselect cell") and tracked_cell :
		clear_selection()

func camera_check_override():
	c_key_was_pressed = true

func camera_zoom():
	if tracked_cell:
		zoom = zoom_level
		anchor_mode = 1
		cell_position = tracked_cell.global_position
		position = cell_position

func camera_unzoom():
	zoom = default_zoom 
	anchor_mode = 0

func on_cell_select(cell):
	cell_select_panel.visible = true
	tracked_cell = cell  # Assume 'cell' is the node to follow

func on_cell_deselect(cell):
	if cell == tracked_cell:
		cell_select_panel.visible = false
		zoom = default_zoom 
		anchor_mode = 0
		cell_position = null
		tracked_cell = null
		cell_stats.clear_stats()

func clear_selection():
	cell_select_panel.visible = false
	zoom = default_zoom 
	anchor_mode = 0
	cell_position = null
	tracked_cell = null
	cell_stats.clear_stats()
	


func _on_zoom_check_toggled(toggled_on):
	cam_focus_check = toggled_on
