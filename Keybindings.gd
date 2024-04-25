extends VBoxContainer

var keybindings = {}

# Called when the node enters the scene tree for the first time.
func _ready():
	update_keybindings_display()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func update_keybindings_display():
	# Clear existing children to prevent duplication
	for child in get_children():
		remove_child(child)
		child.queue_free()

	# Retrieve all actions from the InputMap
	var actions = InputMap.get_actions()
	# Calculate the starting index for the last five actions
	var start_index = max(actions.size() - 5, 0)

	# Only process the last five actions
	for i in range(start_index, actions.size()):
		var action = actions[i]
		var events = InputMap.action_get_events(action)
		for event in events:
			if event is InputEventKey or event is InputEventMouseButton:
				# Create a label for each keybinding
				var label = Label.new()
				label.text = action + ": " + event.as_text()
				add_child(label)
				# Store the event text under the action key for potential future use
				keybindings[action] = event.as_text()

	# Optionally log the current keybindings to the output
	print(keybindings)
