#include "audio_stream_playback_voip.h"

#include <godot_cpp/core/math.hpp>

using namespace godot;


void AudioStreamPlaybackVOIP::_bind_methods(){

}

void AudioStreamPlaybackVOIP::_start(double _){
    active = true;
    samples_processed = 0;
}

void AudioStreamPlaybackVOIP::_stop(){
    active = false;
    base->reset();
}

bool AudioStreamPlaybackVOIP::_is_playing() const{
    return active;
}

void AudioStreamPlaybackVOIP::_tag_used_streams(){

}

// WARNING: REALTIME THREAD
// DO NOT MUTEX LOCK
// DO NOT MALLOC/NEW
int32_t AudioStreamPlaybackVOIP::_mix(AudioFrame *buffer, double rate_scale, int32_t frames){
    if (!active) {
        return 0;
    }
    
    // DEBUG
    for(int i=0; i<frames; i++){
        float sample = sinf(440.0 * 2.0 * Math_PI * (samples_processed + i) / 44100.0);
        buffer[i].left = sample;
        buffer[i].right = sample;
    }
    samples_processed += frames;
    
    return frames;
}