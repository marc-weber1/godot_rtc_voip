#include "register_types.h"

#include "core/object/class_db.h"
#include "voip_client.h"
#include "voip_server.h"

void initialize_godot_rtc_voip_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
    ClassDB::register_class<VOIPClient>();
    ClassDB::register_class<VOIPServer>();
}

void uninitialize_godot_rtc_voip_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
}