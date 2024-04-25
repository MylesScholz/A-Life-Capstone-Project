extends Panel

var toggle_button = null
var main_menu = null
var settings_menu = null

var setting_toggled = true

# Called when the node enters the scene tree for the first time.
func _ready():
	toggle_button = get_parent().get_node("MenuPanel/TabContainer/General/ExtraMenuCheck")
	main_menu = get_parent().get_node("BarPanel")
	settings_menu = get_parent().get_node("MenuPanel/ExitMenuButton")

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	if setting_toggled and !main_menu.visible and !settings_menu.from_main_menu:
		visible = true
	else:
		visible = false


func _on_check_button_2_toggled(_toggled_on):
	setting_toggled = !setting_toggled
