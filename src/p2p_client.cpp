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

void P2PClient::poll() {}