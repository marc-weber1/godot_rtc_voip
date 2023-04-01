extends Node3D

var user = load("res://user.tscn")

var peers = {}


# Called when the node enters the scene tree for the first time.
func _ready():
	print("Audio devices: ", AudioServer.get_input_device_list())
	print("Current device: ", AudioServer.get_input_device())
	$VOIPClient.add_debug_peer()


func _on_voip_client_user_connected(peer: WebRTCPeerConnection, audio_stream: AudioStream):
	print("Client connected")
	var scene_instance = user.instantiate()
	add_child(scene_instance)
	scene_instance.stream = audio_stream
	scene_instance.play()
	
	#peers[peer] = scene_instance


func _on_voip_client_user_disconnected(peer: WebRTCPeerConnection):
	pass
