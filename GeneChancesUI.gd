extends VBoxContainer


func prob_change(name):
	var membrane_prob = get_node("CellMembraneMutationChance/SpinBox").value
	var flagella_prob = get_node("FlagellaMutationChance/SpinBox").value
	var mitochondria_prob = get_node("MitochondriaMutationChance/SpinBox").value
	var nucleus_prob = get_node("NucleusMutationChance/SpinBox").value
	var ribosome_prob = get_node("RibosomeMutationChance/SpinBox").value
	var total_prob = membrane_prob + flagella_prob + mitochondria_prob + nucleus_prob + ribosome_prob
	
	if total_prob >= 101:
		get_node(name+"/SpinBox").value -= total_prob - 100
		#if name != "CellMembraneMutationChance":
			#get_node("CellMembraneMutationChance/SpinBox").value
		#
		#if name != "FlagellaMutationChance":
			#get_node("FlagellaMutationChance/SpinBox").value
		#
		#if name != "MitochondriaMutationChance":
			#get_node("MitochondriaMutationChance/SpinBox").value
		#
		#if name != "NucleusMutationChance":
			#get_node("NucleusMutationChance/SpinBox").value
		#
		#if name != "RibosomeMutationChance":
			#get_node("RibosomeMutationChance/SpinBox").value
