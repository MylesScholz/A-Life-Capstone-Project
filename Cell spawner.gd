extends Node

@export var cell_scene: PackedScene
@export var num_cells: int

func spawnCell():
	var cell = cell_scene.instantiate()
	var cell_edge = cell.get_node("Sprite").texture.get_size()/4
	cell.position = Vector2(randi_range(cell_edge.x, get_viewport().size.x - cell_edge.x),randi_range(cell_edge.y, get_viewport().size.y - cell_edge.y))
	
	add_child(cell)

func _ready():
	for i in range(num_cells):
		spawnCell()
