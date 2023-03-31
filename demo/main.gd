extends Node3D

var user = load("res://user.tscn")

var peers = {}


# Called when the node enters the scene tree for the first time.
func _ready():
	print("Audio devices: ", AudioServer.get_input_device_list())
	print("Current device: ", AudioServer.get_input_device())


func _on_voip_client_user_connected(peer: WebRTCPeerConnection, audio_stream: AudioStreamVOIP):
	var scene_instance = user.instance()
	add_child(scene_instance)
	scene_instance.Stream = audio_stream
	
	peers[peer] = scene_instance


func _on_voip_client_user_disconnected(peer: WebRTCPeerConnection):
	pass
