#include "voip_client.h"

using namespace godot;


void VOIPClient::_bind_methods(){

    ClassDB::bind_method(D_METHOD("set_input"), &VOIPClient::set_input);

    ClassDB::bind_method(D_METHOD("get_input"), &VOIPClient::get_input);

    ClassDB::bind_method(D_METHOD("add_peer"), &VOIPClient::add_peer);
    ClassDB::bind_method(D_METHOD("remove_peer"), &VOIPClient::remove_peer);

    ClassDB::bind_method(D_METHOD("add_debug_peer"), &VOIPClient::add_debug_peer); // DEBUG

    ClassDB::add_property(
        "VOIPClient",
        PropertyInfo(Variant::OBJECT, "input", godot::PROPERTY_HINT_NONE, "", 6U, "AudioStream"),
        "set_input",
        "get_input"
    );


    ADD_SIGNAL( MethodInfo(
        "user_connected",
        PropertyInfo(Variant::INT, "peer_id"),
        PropertyInfo(Variant::OBJECT, "audio_stream", godot::PROPERTY_HINT_RESOURCE_TYPE, "", 6U, "AudioStreamVOIP")
    ));

    ADD_SIGNAL( MethodInfo(
        "user_disconnected",
        PropertyInfo(Variant::INT, "peer_id")
    ));
}

VOIPClient::VOIPClient(){
    // Initialize client to new RTCClient?
}

void VOIPClient::connect_to_server(String ip, String lobby_id){
    //client->connect("user_connected", Callable(this, "player_connected"));
    //client->connect("user_disconnected", Callable(this, "player_disconnected"));
}

void VOIPClient::add_debug_peer(){
    // DEBUG
    Ref<AudioStreamVOIP> peer_stream;
    peer_stream.instantiate();
    peer_streams.append( peer_stream );
    emit_signal("user_connected", 0, peer_stream);
}

void VOIPClient::_physics_process(double _delta){
    if(input.is_null() || peer_streams.size() == 0) return;

    // Read from microphone stream input
    PackedByteArray to_send;
    //input-> ???

    // Send to all peers

    if(to_send.size() > 0){
        for(Ref<AudioStreamVOIP> stream : peer_streams){
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