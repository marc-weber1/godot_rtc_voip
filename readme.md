## What is this?

An attempt at VOIP in Godot 4, with as easy an interface as possible.

Inspired by the features of [V-Sekai's speech module](https://github.com/V-Sekai/godot-speech) and the simplicity of [VOIP for godot 3](https://github.com/ikbencasdoei/godot-voip), designed completely in C++ from the start so that opus / echo cancellation / jitter buffer granulation is possible, but in a GDExtension so that it can be cleanly kept inside an AudioStream.

## The design

Spawn in a VOIPClient node (with your mic as the input AudioStream), and in GDscript somewhere call it like this when a connection is made:

```
var audio_stream = $VOIPClient.add_peer(packet_peer)
```

Where `audio_stream` is a VOIPAudioStream (inheriting from [AudioStream](https://docs.godotengine.org/en/stable/classes/class_audiostream.html)) and `packet_peer` is any kind of [PacketPeer](https://docs.godotengine.org/en/stable/classes/class_packetpeer.html). Play the audio stream in any kind of [AudioStreamPlayer](https://docs.godotengine.org/en/stable/classes/class_audiostreamplayer.html). To use WebRTC, pass a [WebRTCDataChannel](https://docs.godotengine.org/en/stable/classes/class_webrtcdatachannel.html) as the packet peer, after it has been opened (example of this in the demo project, adapted from [here](https://github.com/godotengine/godot-demo-projects/tree/master/networking/webrtc_signaling)).

When the packet peer is closed, make sure anything that is playing the audio stream is stopped, and call:

```
$VOIPClient.remove_peer(packet_peer)
```

## To build

Clone this repository with all submodules with `git clone https://github.com/marc-weber1/godot_rtc_voip.git --recurse-submodules` and then:
```
scons platform=[windows/linux]
```
Make sure the [WebRTC Native GDExtension](https://github.com/godotengine/webrtc-native) is also in your project.