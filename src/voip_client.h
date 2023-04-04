#ifndef VOIP_CLIENT_H
#define VOIP_CLIENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/templates/vector.hpp>

#include "rtc_client.h"
#include "audio_stream_voip.h"


namespace godot {


class VOIPClient : public Node {
    GDCLASS(VOIPClient, Node);

private:
    Ref<AudioStream> input;
    Ref<P2PClient> client;
    //HashMap<long, Ref<AudioStreamVOIP>> peer_streams; // peer_id: output_stream
    Vector<Ref<AudioStreamVOIP>> peer_streams; // DEBUG

protected:
    static void _bind_methods();

public:
    VOIPClient();
    void connect_to_server(String ip, String lobby_id);
    void add_debug_peer(); // DEBUG

    void set_input(Ref<AudioStream>);
    Ref<AudioStream> get_input() const;
    void set_client(Ref<P2PClient>);
    Ref<P2PClient> get_client();

    // Signal handlers
    void player_connected(int peer_id);
    void player_disconnected(int peer_id);
};


}

#endif