#ifndef VOIP_SERVER_H
#define VOIP_SERVER_H

#include <godot_cpp/classes/node.hpp>

namespace godot {


class VOIPServer : public Node {
    GDCLASS(VOIPServer, Node)

protected:
    static void _bind_methods();

public:
    VOIPServer();

};


};

#endif