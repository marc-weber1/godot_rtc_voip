// Based on https://github.com/godotengine/godot-demo-projects/blob/master/networking/webrtc_signaling/client

#ifndef RTC_CLIENT_H
#define RTC_CLIENT_H

#include <godot_cpp/classes/web_socket_peer.hpp>
#include <godot_cpp/classes/web_rtc_multiplayer_peer.hpp>

#include "p2p_client.h"

namespace godot {


class RTCClient : public P2PClient {
    GDCLASS(RTCClient, P2PClient)

private:
    enum Message{
        JOIN,
        ID,
        PEER_CONNECT,
        PEER_DISCONNECT,
        OFFER,
        ANSWER,
        CANDIDATE,
        SEAL
    };

    WebSocketPeer handshake_ws;
    WebRTCMultiplayerPeer rtc_mp;

    bool parse_handshake_message();
    Error send_msg(Message type, int id, String data="");

public:
    bool autojoin;

    RTCClient();
    void join_lobby(String lobby_id);
    void poll() override; // Called by VOIPClient

    virtual void connect_to_server(String ip);
    virtual void disconnect_from_server();

};


}

#endif