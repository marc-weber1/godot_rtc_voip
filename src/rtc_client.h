// Based on https://github.com/godotengine/godot-demo-projects/blob/master/networking/webrtc_signaling/client

#ifndef RTC_CLIENT_H
#define RTC_CLIENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/web_socket_peer.hpp>
#include <godot_cpp/classes/web_rtc_multiplayer_peer.hpp>

namespace godot {


class RTCClient : public Node {

private:
    WebSocketPeer ws;
    WebRTCMultiplayerPeer rtc_mp;

protected:
    static void _bind_methods();

public:
    virtual void _physics_process(double) override;

};


}

#endif