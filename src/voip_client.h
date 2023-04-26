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
    bool muted;

    Ref<AudioStreamPlayback> input_playback; // Should always exist if input does
    Vector<Ref<AudioStreamVOIP>> peer_streams;
    double mic_time_processed; // in seconds

protected:
    static void _bind_methods();

public:
    const double FRAME_SIZE = 0.02; // in seconds
    const int BITRATE = 12000; // in bits/second
    const double SAMPLE_RATE = 44100.; // in hz, maybe get this from somewhere else


    void _ready() override;


    void _physics_process(double) override;
    void send_input(double);


    void set_muted(bool);
    bool is_muted() const;

    void set_input(Ref<AudioStream>);
    Ref<AudioStream> get_input() const;


    Ref<AudioStreamVOIP> add_peer(Ref<PacketPeer> peer);
    void remove_peer(Ref<PacketPeer> peer);
};


}

#endif