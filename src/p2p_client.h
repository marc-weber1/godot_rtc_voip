// An abstract P2P client, inherit this and override connect(),
// emit signals "user_connected" and "user_disconnected"
// pass extra information with the constructor and setters
// in the inherited class

#ifndef P2P_CLIENT_H
#define P2P_CLIENT_H

#include <godot_cpp/classes/node.hpp>

namespace godot {


class P2PClient : public Node {
    GDCLASS(P2PClient, Node) // Should this be GDEXTENSION_CLASS ?

protected:
    static void _bind_methods();
    template <class T, class B>
    static void register_virtuals();

public:
    virtual void connect_to_server();
    virtual void disconnect_from_server();

};


}

#endif