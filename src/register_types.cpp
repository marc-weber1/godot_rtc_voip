#include "register_types.h"

#include "voip_client.h"
#include "audio_stream_voip.h"
#include "audio_stream_playback_voip.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>


using namespace godot;

void initialize_voip_rtc_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<VOIPClient>();
    ClassDB::register_class<AudioStreamVOIP>();
    ClassDB::register_class<AudioStreamPlaybackVOIP>();
}

void uninitialize_voip_rtc_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT voip_rtc_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

    init_obj.register_initializer(initialize_voip_rtc_module);
    init_obj.register_terminator(uninitialize_voip_rtc_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}