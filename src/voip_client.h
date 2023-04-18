#ifndef VOIP_CLIENT_H
#define VOIP_CLIENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/templates/vector.hpp>

#include "audio_stream_voip.h"


namespace godot {


class VOIPClient : public Node {
    GDCLASS(VOIPClient, Node);

private:
    Ref<AudioStream> input;
    //HashMap<long, Ref<AudioStreamVOIP>> peer_streams; // peer_id: output_stream
    Vector<Ref<AudioStreamVOIP>> peer_streams; // DEBUG

protected:
    static void _bind_methods();

public:
    VOIPClient();
    void connect_to_server(String ip, String lobby_id);
    void add_debug_peer(); // DEBUG

    void _physics_process(double) override;

    void set_input(Ref<AudioStream>);
    Ref<AudioStream> get_input() const;

    // Signal handlers
    Ref<AudioStreamVOIP> add_peer(Ref<PacketPeer> peer);
    void remove_peer(Ref<PacketPeer> peer);
};


}

#endif