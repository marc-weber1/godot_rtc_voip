#include "audio_stream_voip.h"
#include "audio_stream_playback_voip.h"

using namespace godot;


AudioStreamVOIP::AudioStreamVOIP(Ref<WebRTCPeerConnection> _peer_conn) : peer_conn(_peer_conn) {

}

void AudioStreamVOIP::reset(){

}

void AudioStreamVOIP::_bind_methods(){
    ClassDB::bind_method(D_METHOD("get_stream_name"), &AudioStreamVOIP::_get_stream_name);
}

Ref<AudioStreamPlayback> AudioStreamVOIP::_instantiate_playback() const{
    Ref<AudioStreamPlaybackVOIP> playback;
	playback.instantiate();
	playback->base = Ref<AudioStreamVOIP>(this);
	return playback;
}