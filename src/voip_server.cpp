#include "voip_server.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


void VOIPServer::_bind_methods(){

}

VOIPServer::VOIPServer(){
    UtilityFunctions::print("Loaded");
}