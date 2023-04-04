#include "p2p_client.h"

using namespace godot;


void P2PClient::_bind_methods(){


    ADD_SIGNAL( MethodInfo(
        "user_connected",
        PropertyInfo(Variant::INT, "peer_id")
    ));

    ADD_SIGNAL( MethodInfo(
        "user_disconnected",
        PropertyInfo(Variant::INT, "peer_id")
    ));
}

template <class T, class B>
void P2PClient::register_virtuals(){
    Node::register_virtuals<T, B>();

    // I honestly have no idea what I'm doing here, hope this works
    // Supposed to let people override the connect() method
    if constexpr (!std::is_same_v<decltype(&B::connect_to_server),decltype(&T::connect_to_server)>) {
        BIND_VIRTUAL_METHOD(T, connect_to_server);
    }
}

void P2PClient::connect_to_server() {}

void P2PClient::disconnect_from_server() {}