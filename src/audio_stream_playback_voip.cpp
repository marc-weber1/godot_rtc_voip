#include "audio_stream_playback_voip.h"

using namespace godot;


void AudioStreamPlaybackVOIP::_bind_methods(){

}

void AudioStreamPlaybackVOIP::_start(double _){

}

void AudioStreamPlaybackVOIP::_stop(){

}

bool AudioStreamPlaybackVOIP::_is_playing() const{
    return false;
}

void AudioStreamPlaybackVOIP::_tag_used_streams(){

}

int32_t AudioStreamPlaybackVOIP::_mix(AudioFrame *buffer, double rate_scale, int32_t frames){
    return 0;
}