extends TextureButton

# Needs a way for c++ scripts to still run when paused for
# things like the fps counter, main menu and reset buttons
var main_menu =  null

var normal_texture = null
var pressed_texture = null

var pressed_check = false

func _pressed():
	# Toggle the button state
	pressed_check = !pressed_check
	
	# Update the button texture based on the new state
	if pressed_check:
		texture_normal = pressed_texture
	else:
		texture_normal = normal_texture
	# Call the pause functionality
	pause_functionality()

func pause_functionality():
	
	GlobalVariables.paused = !GlobalVariables.paused # Note that button was clicked
	GlobalVariables.used_pause_button = !GlobalVariables.used_pause_button
	
	GlobalVariables.time_scale_backup_two = Engine.time_scale # Save prev delta
	Engine.time_scale = GlobalVariables.time_scale_backup_one # Set delta
	GlobalVariables.time_scale_backup_one = GlobalVariables.time_scale_backup_two

func unpause(): # If paused, unpause
	if (Engine.time_scale == 0):
		texture_normal = normal_texture
		pause_functionality()

func pause(): # If unpaused, pause
	if (Engine.time_scale != 0):
		texture_normal = pressed_texture
		pause_functionality()

# Called when the node enters the scene tree for the first time.
func _ready():
	process_mode = Node.PROCESS_MODE_ALWAYS
	main_menu = get_parent()
	
	normal_texture = preload("res://.godot/imported/PauseButton.svg-c19b0b3e074f1bde5bea559e3f4d590f.ctex")
	pressed_texture = preload("res://.godot/imported/PlayButton.svg-f0713277366c75169143302a73e4216d.ctex")

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
