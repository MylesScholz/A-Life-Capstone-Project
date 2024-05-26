extends SpinBox


# Changes min so cant be above max
func _value_changed(value):
	var min_spin_box = get_parent().find_child("SpinBoxMin")
	min_spin_box.max_value = value
