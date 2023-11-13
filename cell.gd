extends RigidBody2D

var speed = randf_range(150.0,250.0)

func _ready():
	randomize()

func _process(delta):
	var direction = randf_range(0,2*PI)
	
	var velocity = Vector2.UP.rotated(direction) * speed
	position += velocity * delta
