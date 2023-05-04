#include "voip_client.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/audio_frame.hpp>
#include <godot_cpp/classes/web_rtc_data_channel.hpp>
#include <vector>

using namespace godot;


void VOIPClient::_bind_methods(){

    ClassDB::bind_method(D_METHOD("add_peer"), &VOIPClient::add_peer);
    ClassDB::bind_method(D_METHOD("remove_peer"), &VOIPClient::remove_peer);

    ClassDB::bind_method(D_METHOD("set_input"), &VOIPClient::set_input);
    ClassDB::bind_method(D_METHOD("get_input"), &VOIPClient::get_input);
    ClassDB::add_property(
        "VOIPClient",
        PropertyInfo(Variant::OBJECT, "input", godot::PROPERTY_HINT_NONE, "", 6U, "AudioStream"),
        "set_input",
        "get_input"
    );

    ClassDB::bind_method(D_METHOD("set_muted"), &VOIPClient::set_muted);
    ClassDB::bind_method(D_METHOD("is_muted"), &VOIPClient::is_muted);
    ClassDB::add_property(
        "VOIPClient",
        PropertyInfo(Variant::BOOL, "muted", godot::PROPERTY_HINT_NONE, "", 6U, "bool"),
        "set_muted",
        "is_muted"
    );
}


void VOIPClient::_ready(){
    set_muted(muted);
}

void VOIPClient::_physics_process(double _delta){
    send_input(_delta);
}

// Send the last 0.016 seconds of audio as packets to all active peers
void VOIPClient::send_input(double _delta){
    if(input.is_null() || peer_streams.size() == 0) return;
    if(input_playback.is_null()) return;


    // Poll all connections (if needed)

    for(Ref<AudioStreamVOIP> stream : peer_streams){
        if(stream.is_null() || stream->peer_conn.is_null()){ // Should never happen, but just in case
            continue; // Remove from array if nullptr?
        }

        if(stream->peer_conn->get_class() == "WebRTCLibDataChannel"){ // Won't work for web platforms but dynamic cast to WebRTCDataChannel doesnt work
            WebRTCDataChannel *channel = (WebRTCDataChannel *) (stream->peer_conn.ptr());
            channel->poll();
        }
    }


    // Read from microphone stream input (very janky?? is there no way to check how many samples we can read?)

    int frames = (int) (floor((mic_time_processed + _delta) / FRAME_SIZE) - floor(mic_time_processed / FRAME_SIZE));
    mic_time_processed += _delta;
    if(frames <= 0) return;
    double time_to_process = frames * FRAME_SIZE;
    int samples_to_process = (int) (time_to_process * SAMPLE_RATE);

    std::vector<AudioFrame> samples_to_send(samples_to_process, {0., 0.});
    input_playback->_mix(samples_to_send.data(), 1., samples_to_process);



    // Convert to packets

    for(int frame=0; frame<frames; frame++){
        PackedByteArray packet;

        int samples_per_frame = (int) (FRAME_SIZE * SAMPLE_RATE);
        for(int s=frame*samples_per_frame; s<(frame+1)*samples_per_frame; s++){
            packet.push_back(samples_to_send[s].left); // mono
        }


        // Send to all peers

        for(Ref<AudioStreamVOIP> stream : peer_streams){
            if(stream.is_null() || stream->peer_conn.is_null()){ // Should never happen, but just in case
                continue; // Remove from array if nullptr?
            }

            stream->peer_conn->put_packet(packet); // Convert to big endian first?
        }
    }
}


// Sets + Gets

void VOIPClient::set_input(const Ref<AudioStream> _in){
    input = _in;
    if(input.is_null()) return;

    input_playback = input->instantiate_playback();
    set_muted(muted);
}

Ref<AudioStream> VOIPClient::get_input() const{
    return input;
}

void VOIPClient::set_muted(bool mute){
    UtilityFunctions::print("VOIPClient: set_muted ", mute);

    if(!mute && !input_playback.is_null()){
        mic_time_processed = 0.;
    }
    else if(mute && !input_playback.is_null()){
        input_playback->_stop();
    }

    muted = mute;
}

bool VOIPClient::is_muted() const{
    return muted;
}

Ref<AudioStreamVOIP> VOIPClient::add_peer(Ref<PacketPeer> peer){
    Ref<AudioStreamVOIP> ret;
    ret.instantiate();
    ret->peer_conn = peer;
    peer_streams.push_back(ret);
    return ret;
}

void VOIPClient::remove_peer(Ref<PacketPeer> peer){
    for(int i=0; i<peer_streams.size(); i++){
        if(peer_streams[i]->peer_conn == peer){
            peer_streams.remove_at(i);
            break;
        }
    }
}