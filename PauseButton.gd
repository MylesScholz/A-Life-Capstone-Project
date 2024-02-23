extends TextureButton

# Needs a way for c++ scripts to still run when paused for
# things like the fps counter, main menu and reset buttons

func _pressed():
	get_child(!get_tree().paused).visible = false
	get_child(get_tree().paused).visible = true
	get_tree().paused = !get_tree().paused

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass


func _on_menu_button_pressed():
	_pressed()
