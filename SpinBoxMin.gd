extends SpinBox


# Changes max so cant be below min
func _value_changed(value):
	var max_spin_box = get_parent().find_child("SpinBoxMax")
	max_spin_box.min_value = value
