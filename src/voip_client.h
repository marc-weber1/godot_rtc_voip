#ifndef VOIP_CLIENT_H
#define VOIP_CLIENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/classes/web_rtc_multiplayer_peer.hpp>

#include "audio_stream_voip.h"


namespace godot {


class VOIPClient : public Node {
    GDCLASS(VOIPClient, Node);

private:
    Ref<AudioStream> input;
    WebRTCMultiplayerPeer rtc_mp;
    //HashMap<int, Ref<AudioStreamVOIP>> peer_streams; // peer_id: output_stream
    Vector<Ref<AudioStreamVOIP>> peer_streams; // DEBUG

protected:
    static void _bind_methods();

public:
    VOIPClient();
    void add_debug_peer();

    void set_input(Ref<AudioStream>);
    Ref<AudioStream> get_input() const;
};


}

#endif