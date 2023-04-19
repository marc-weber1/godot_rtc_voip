#include "voip_client.h"

using namespace godot;


void VOIPClient::_bind_methods(){

    ClassDB::bind_method(D_METHOD("set_input"), &VOIPClient::set_input);

    ClassDB::bind_method(D_METHOD("get_input"), &VOIPClient::get_input);

    ClassDB::bind_method(D_METHOD("add_peer"), &VOIPClient::add_peer);
    ClassDB::bind_method(D_METHOD("remove_peer"), &VOIPClient::remove_peer);

    ClassDB::add_property(
        "VOIPClient",
        PropertyInfo(Variant::OBJECT, "input", godot::PROPERTY_HINT_NONE, "", 6U, "AudioStream"),
        "set_input",
        "get_input"
    );
}

VOIPClient::VOIPClient(){
}

void VOIPClient::_physics_process(double _delta){
    if(input.is_null() || peer_streams.size() == 0) return;

    // Read from microphone stream input
    PackedByteArray to_send;
    //input-> ???

    // Send to all peers

    if(to_send.size() > 0){
        for(Ref<AudioStreamVOIP> stream : peer_streams){
            if(stream.is_null() || stream->peer_conn.is_null()){ // Should never happen, but just in case
                continue; // Remove from array if nullptr?
            }

            stream->peer_conn->put_packet(to_send);
        }
    }
}


// Sets + Gets

void VOIPClient::set_input(const Ref<AudioStream> _in){
    input = _in;
}

Ref<AudioStream> VOIPClient::get_input() const{
    return input;
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