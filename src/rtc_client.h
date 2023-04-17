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

    // Handle WebRTCMultiplayerPeer
    String lobby;
    bool sealed = false;
    void lobby_joined(String lobby);
    void connected(int64_t src_id, bool use_mesh);
    void disconnected();
    void peer_connected(int32_t id);
    void peer_disconnected(int32_t id);
    void offer_received(int32_t id, String offer);
    void answer_received(int32_t id, String answer);
    void candidate_received(int32_t id, String mid, int64_t index, String sdp);
    void lobby_sealed();
    void offer_created(String type, String data, int32_t id);
    void new_ice_candidate(String mid_name, String index_name, String sdp_name, int64_t id);

public:
    bool autojoin;

    RTCClient();
    Error join_lobby(String lobby_id);
    void poll() override; // Called by VOIPClient

    virtual void connect_to_server(String ip);
    virtual void disconnect_from_server();

};


}

#endif