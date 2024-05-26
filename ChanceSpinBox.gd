extends SpinBox

func _value_changed(value):
	var allChancesParent = get_parent().get_parent()
	allChancesParent.call("prob_change", get_parent().name)
