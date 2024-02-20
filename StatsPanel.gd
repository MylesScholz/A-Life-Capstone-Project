extends Panel

var dragging = false
var drag_offset = Vector2()

# Called when the node enters the scene tree for the first time.
func _ready():
	mouse_filter = Control.MOUSE_FILTER_STOP

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_stats_exit_button_pressed():
	visible = false

func _gui_input(event):
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT:
		if event.pressed:
			# Start dragging and calculate the offset when the mouse button is pressed.
			dragging = true
			drag_offset = get_global_mouse_position() - global_position
		else:
			# Stop dragging when the mouse button is released.
			dragging = false
		# Consume the event to prevent further processing.
		accept_event()

	if event is InputEventMouseMotion and dragging:
		# Update the panel's global position smoothly using the drag offset.
		global_position = get_global_mouse_position() - drag_offset
		# Consume the event to prevent further processing.
		accept_event()


func _on_stats_open_button_pressed():
	visible = true # Show the stats panel again.
