extends TextureButton

# Should not be able to unpause when in menu

func _pressed():
	get_parent().get_parent().get_parent().visible = false

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
