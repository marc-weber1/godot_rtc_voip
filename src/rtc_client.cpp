#include "rtc_client.h"

#include <godot_cpp/classes/json.hpp>

using namespace godot;


RTCClient::RTCClient(){

}

void RTCClient::poll(){
    WebSocketPeer::State old_state = handshake_ws.get_ready_state();
    if(old_state == WebSocketPeer::STATE_CLOSED){
        return;
    }

    handshake_ws.poll();
    WebSocketPeer::State state = handshake_ws.get_ready_state();
    if(state != old_state && state == WebSocketPeer::STATE_OPEN && autojoin){
        // Connected to handshake server
        emit_signal("server_connected");

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
        emit_signal("server_disconnected");
    }
}

void RTCClient::join_lobby(String lobby_id){

}

bool RTCClient::parse_handshake_message(){
    Variant parsed = JSON::parse_string(handshake_ws.get_packet().get_string_from_utf8());
    // Todo
    return true;
}

Error RTCClient::send_msg(Message type, int id, String data){
    Dictionary msg;
    msg["type"] = type;
    msg["id"] = id;
    msg["data"] = data;
    return handshake_ws.send_text(JSON::stringify(msg));
}

void RTCClient::connect_to_server(String ip){
    disconnect_from_server();
    handshake_ws.connect_to_url(ip);
}

void RTCClient::disconnect_from_server(){
    handshake_ws.close();
}