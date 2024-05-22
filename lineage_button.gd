extends TextureButton

var target_cell = null
var luca_targeted = false
var lineage_camera = null
var ui_cam = null

func set_cell(cell, luca):
	target_cell = cell
	luca_targeted = luca

func _pressed():
	if luca_targeted:
		lineage_camera.select_luca()
		ui_cam.clear_selection()
	if target_cell and not luca_targeted:
		lineage_camera.select_cell(target_cell)
		ui_cam.on_cell_select(target_cell)

# Called when the node enters the scene tree for the first time.
func _ready():
	lineage_camera = find_parent("Lineage").find_child("LineageCamera")
	ui_cam = find_parent("CellSpawner").find_child("UI_Cam")
