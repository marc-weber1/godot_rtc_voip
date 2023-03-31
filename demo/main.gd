extends Node3D


# Called when the node enters the scene tree for the first time.
func _ready():
	print("Audio devices: ", AudioServer.get_input_device_list())
	print("Current device: ", AudioServer.get_input_device())


func _on_voip_client_user_connected(peer: WebRTCMultiplayerPeer, audio_stream: AudioStream):
	pass # Replace with function body.


func _on_voip_client_user_disconnected(peer: WebRTCMultiplayerPeer):
	pass # Replace with function body.
