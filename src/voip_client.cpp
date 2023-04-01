#include "voip_client.h"

using namespace godot;


void VOIPClient::_bind_methods(){

    ClassDB::bind_method(D_METHOD("set_input"), &VOIPClient::set_input);

    ClassDB::bind_method(D_METHOD("get_input"), &VOIPClient::get_input);

    ClassDB::bind_method(D_METHOD("add_debug_peer"), &VOIPClient::add_debug_peer); // DEBUG

    ClassDB::add_property(
        "VOIPClient",
        PropertyInfo(Variant::OBJECT, "input", godot::PROPERTY_HINT_NONE, "", 6U, "AudioStream"),
        "set_input",
        "get_input"
    );


    ADD_SIGNAL( MethodInfo(
        "user_connected",
        PropertyInfo(Variant::OBJECT, "peer", godot::PROPERTY_HINT_NONE, "", 6U, "WebRTCPeerConnection"),
        PropertyInfo(Variant::OBJECT, "audio_stream", godot::PROPERTY_HINT_NONE, "", 6U, "AudioStreamVOIP")
    ));

    ADD_SIGNAL( MethodInfo(
        "user_disconnected",
        PropertyInfo(Variant::OBJECT, "peer", godot::PROPERTY_HINT_NONE, "", 6U, "WebRTCPeerConnection")
    ));
}

VOIPClient::VOIPClient(){
}

void VOIPClient::add_debug_peer(){
    // DEBUG
    Ref<WebRTCPeerConnection> peer_conn = new WebRTCPeerConnection();
    Ref<AudioStreamVOIP> peer_stream = new AudioStreamVOIP(peer_conn);
    peer_streams.append( peer_stream );
    emit_signal("user_connected", peer_conn, peer_stream);
}

void VOIPClient::set_input(const Ref<AudioStream> _in){
    input = _in;
}

Ref<AudioStream> VOIPClient::get_input() const{
    return input;
}