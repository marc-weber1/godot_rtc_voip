#include "rtc_client.h"

using namespace godot;


void RTCClient::_bind_methods(){


    ADD_SIGNAL( MethodInfo(
        "user_connected",
        PropertyInfo(Variant::INT, "peer_id")
    ));

    ADD_SIGNAL( MethodInfo(
        "user_disconnected",
        PropertyInfo(Variant::INT, "peer_id")
    ));
}

void RTCClient::_physics_process(double _d){

}