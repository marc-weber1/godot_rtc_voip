#ifndef VOIP_CLIENT_H
#define VOIP_CLIENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/templates/vector.hpp>

namespace godot {


class VOIPClient : public Node {
    GDCLASS(VOIPClient, Node);

private:
    Ref<AudioStream> input;

protected:
    static void _bind_methods();

public:
    VOIPClient();

    void set_input(Ref<AudioStream>);
    Ref<AudioStream> get_input() const;
};


}

#endif