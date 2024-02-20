extends TextureButton

var delta_multiplier = 1;

func _pressed():
	delta_multiplier += .5

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
