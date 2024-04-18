extends Camera2D

var tracked_cell = null
var default_zoom = Vector2(1, 1)
var zoom_level = Vector2(1.7, 1.7)
var cell_position = null

var exit_zoom = false

# Called when the node enters the scene tree for the first time.
func _ready():
	anchor_mode = 0
	zoom = default_zoom
	set_process_input(true)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if tracked_cell and !exit_zoom :
		zoom = zoom_level
		anchor_mode = 1
		cell_position = tracked_cell.global_position
		position = cell_position
		
		# keybinding to exit zoom functionality
		if Input.is_key_pressed(KEY_Q):
			exit_zoom = true
			reset_zoom()


func zoom_on_cell (cell):
	tracked_cell = cell  # Assume 'cell' is the node to follow
	exit_zoom = false


func reset_zoom ():
	anchor_mode = 0
	zoom = default_zoom
