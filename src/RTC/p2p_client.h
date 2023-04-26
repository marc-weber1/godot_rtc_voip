// An abstract P2P client, inherit this and
//  emit signals "user_connected", "user_disconnected",
//  "server_connected", and "server_disconnected"
// VOIPClient will use these signals

#ifndef P2P_CLIENT_H
#define P2P_CLIENT_H

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {


class P2PClient : public RefCounted {
    GDCLASS(P2PClient, RefCounted) // Should this be GDEXTENSION_CLASS ?

protected:
    static void _bind_methods();

public:
    virtual void poll(); // VOIPClient will call this regularly

};


}

#endif