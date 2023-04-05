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

    ADD_SIGNAL( MethodInfo(
        "server_connected"
    ));

    ADD_SIGNAL( MethodInfo(
        "server_disconnected"
    ));

    BIND_VIRTUAL_METHOD(P2PClient, poll);
}

/*template <class T, class B>
void P2PClient::register_virtuals(){
    RefCounted::register_virtuals<T, B>();

    // I honestly have no idea what I'm doing here, hope this works
    // Supposed to let people override the poll() method
    if constexpr (!std::is_same_v<decltype(&B::poll),decltype(&T::poll)>) {
        BIND_VIRTUAL_METHOD(T, poll);
    }
}*/

void P2PClient::poll() {}