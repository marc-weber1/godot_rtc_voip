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
    WebSocketPeer handshake_ws;
    WebRTCMultiplayerPeer rtc_mp;

    void poll_handshake();
    bool parse_handshake_message();

public:
    bool autojoin;

    RTCClient(String ip, String lobby_id);
    void join_lobby(String lobby_id);

    virtual void _physics_process(double) override;
    virtual void connect_to_server() override;
    virtual void disconnect_from_server() override;

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

};


}

#endif