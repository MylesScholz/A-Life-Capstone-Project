extends Label

var on = false
func toggle_display(): # Displays nothing is simulation is not running
	on = !on
	if (!on):
		set_text("")
	else:
		set_text("Speed: " + str(Engine.time_scale) + "x")

func update_speed_display(speed):
	set_text("Speed: " + str(speed) + "x")