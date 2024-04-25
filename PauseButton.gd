extends TextureButton

# Needs a way for c++ scripts to still run when paused for
# things like the fps counter, main menu and reset buttons
var main_menu =  null

func _pressed():
	pause()

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS
	main_menu = get_parent()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	if Input.is_action_just_pressed("pause") and main_menu.visible:
		pause()

func pause():
	get_child(!get_tree().paused).visible = false # Change pause button visually
	get_child(get_tree().paused).visible = true
	get_tree().paused = !get_tree().paused # Pause and unpause
	GlobalVariables.used_pause_button = !GlobalVariables.used_pause_button
	
