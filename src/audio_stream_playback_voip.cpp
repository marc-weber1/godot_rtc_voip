#include "audio_stream_playback_voip.h"

#include <godot_cpp/core/math.hpp>

using namespace godot;


void AudioStreamPlaybackVOIP::_start(double _){
    active = true;
    samples_processed = 0;
}

void AudioStreamPlaybackVOIP::_stop(){
    active = false;
}

bool AudioStreamPlaybackVOIP::_is_playing() const{
    return active;
}



// WARNING: REALTIME THREAD
// DO NOT MUTEX LOCK
// DO NOT MALLOC/NEW
int32_t AudioStreamPlaybackVOIP::_mix(AudioFrame *buffer, double rate_scale, int32_t frames){
    if (!active || base.is_null() || base->peer_conn.is_null()) {
        return 0;
    }
    
    // Debug, just throw away the packets
    for(int i=0; base->peer_conn->get_available_packet_count() > 0; i++){
        PackedByteArray packet = base->peer_conn->get_packet();
    }
    samples_processed += frames;
    
    return frames;
}