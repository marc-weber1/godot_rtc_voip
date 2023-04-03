#include "voip_client.h"

using namespace godot;


void VOIPClient::_bind_methods(){

    ClassDB::bind_method(D_METHOD("set_input"), &VOIPClient::set_input);

    ClassDB::bind_method(D_METHOD("get_input"), &VOIPClient::get_input);

    ClassDB::bind_method(D_METHOD("player_connected"), &VOIPClient::player_connected);
    ClassDB::bind_method(D_METHOD("player_disconnected"), &VOIPClient::player_connected);

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
}

void VOIPClient::connect(String ip){
    rtc_client.connect("user_connected", Callable(this, "player_connected"));
    rtc_client.connect("user_disconnected", Callable(this, "player_disconnected"));
}

void VOIPClient::add_debug_peer(){
    // DEBUG
    Ref<AudioStreamVOIP> peer_stream;
    peer_stream.instantiate();
    peer_streams.append( peer_stream );
    emit_signal("user_connected", 0, peer_stream);
}

void VOIPClient::set_input(const Ref<AudioStream> _in){
    input = _in;
}

Ref<AudioStream> VOIPClient::get_input() const{
    return input;
}


// Signals

void VOIPClient::player_connected(int peer_id){

}

void VOIPClient::player_disconnected(int peer_id){

}