extends Cell

# Called when the node enters the scene tree for the first time.
func _ready():
	self.set_pickable(true)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _input_event(viewport, event, shape_idx):
	if event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
		GlobalSignals.emit_signal("cell_selected", self)
