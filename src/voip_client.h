#ifndef VOIP_CLIENT_H
#define VOIP_CLIENT_H

#include <godot_cpp/classes/node.hpp>

namespace godot {


class VOIPClient : public Node {
    GDCLASS(VOIPClient, Node);

protected:
    static void _bind_methods();

public:
    VOIPClient();
};


}

#endif