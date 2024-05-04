extends Node

var used_pause_button = false # Marks if pause button was used to pause so action can pause situationally
var paused = false
var time_scale_backup_one = 0.0
var time_scale_backup_two = 0.0
var min_speed = .5 # Should be able to be multiplied by 2 enough times to get 1
var max_speed = 2 # Should be able to be divided by 2 enough times to get 1
