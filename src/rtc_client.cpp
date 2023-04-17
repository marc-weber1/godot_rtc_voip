#include "rtc_client.h"

#include <godot_cpp/classes/json.hpp>

using namespace godot;


RTCClient::RTCClient(){

}

void RTCClient::connect_to_server(String ip){
    disconnect_from_server();
    handshake_ws.connect_to_url(ip);
}

void RTCClient::disconnect_from_server(){
    handshake_ws.close();
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

bool RTCClient::parse_handshake_message(){
    Variant parsed = JSON::parse_string(handshake_ws.get_packet().get_string_from_utf8());
    if(parsed.get_type() != Variant::DICTIONARY || !parsed.has_key("type") || !parsed.has_key("id") || parsed.get("data").get_type() != Variant::STRING)
        return false;

    Dictionary msg = (Dictionary) parsed;
    if(!((String) msg["type"]).is_valid_int() || !((String) msg["id"]).is_valid_int())
        return false;

    int64_t type = ((String) msg["type"]).to_int();
    int64_t src_id = ((String) msg["id"]).to_int();
    String data = (String) msg["data"];

    PackedStringArray candidate;
    switch(type){
        case Message::ID:
            connected(src_id, data == "true");
            break;
        case Message::JOIN:
            lobby_joined(data);
            break;
        case Message::SEAL:
            lobby_sealed();
            break;
        case Message::PEER_CONNECT:
            peer_connected(src_id);
            break;
        case Message::PEER_DISCONNECT:
            peer_disconnected(src_id);
            break;
        case Message::OFFER:
            offer_received(src_id, data);
            break;
        case Message::ANSWER:
            answer_received(src_id, data);
            break;
        case Message::CANDIDATE:
            candidate = data.split("\n", false);
            if(candidate.size() != 3) return false;
            if(!candidate[1].is_valid_int()) return false;
            candidate_received(src_id, candidate[0], candidate[1].to_int(), candidate[2]);
            break;
        default:
            return false;
            break;

        return true; // Parsed
    }

    return true;
}

Error RTCClient::send_msg(Message type, int id, String data){
    Dictionary msg;
    msg["type"] = type;
    msg["id"] = id;
    msg["data"] = data;
    return handshake_ws.send_text(JSON::stringify(msg));
}

void RTCClient::join_lobby(String lobby_id){

}


void godot::RTCClient::lobby_joined(String lobby)
{
}

void godot::RTCClient::connected(int64_t src_id, bool use_mesh)
{
}

void godot::RTCClient::disconnected()
{
}

void godot::RTCClient::peer_connected(int64_t id)
{
}

void godot::RTCClient::peer_disconnected(int64_t id)
{
}

void godot::RTCClient::offer_received(int64_t id, String offer)
{
}

void godot::RTCClient::answer_received(int64_t id, String answer)
{
}

void godot::RTCClient::candidate_received(int64_t id, String mid, int64_t index, String sdp)
{
}

void godot::RTCClient::lobby_sealed()
{
}
