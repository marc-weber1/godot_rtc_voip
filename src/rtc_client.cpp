#include "rtc_client.h"

#include <godot_cpp/classes/json.hpp>

using namespace godot;


RTCClient::RTCClient(String ip, String lobby_id){

}

void RTCClient::_physics_process(double _d){
    poll_handshake(); // Connect & check for new connections
}

void RTCClient::poll_handshake(){
    WebSocketPeer::State old_state = handshake_ws.get_ready_state();
    if(old_state == WebSocketPeer::STATE_CLOSED){
        return;
    }

    handshake_ws.poll();
    WebSocketPeer::State state = handshake_ws.get_ready_state();
    if(state != old_state && state == WebSocketPeer::STATE_OPEN && autojoin){
        // Connected to handshake server

        join_lobby("a"); // Request connection to all others in lobby
    }

    while( state == WebSocketPeer::STATE_OPEN && handshake_ws.get_available_packet_count() ){
        if(!parse_handshake_message()){
            // Unrecognized message
        }
    }

    if(state == WebSocketPeer::STATE_CLOSED){
        int code = handshake_ws.get_close_code();
        String reason = handshake_ws.get_close_reason();

        // Handshake server disconnected
    }
}

void RTCClient::join_lobby(String lobby_id){

}

bool RTCClient::parse_handshake_message(){
    Variant parsed = JSON::parse_string(handshake_ws.get_packet().get_string_from_utf8());
}

void RTCClient::connect_to_server(){
    
}

void RTCClient::disconnect_from_server(){
    handshake_ws.close(); // Just in case we disconnect while connecting

}