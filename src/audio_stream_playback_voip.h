#ifndef AUDIO_STREAM_PLAYBACK_VOIP_H
#define AUDIO_STREAM_PLAYBACK_VOIP_H

#include <godot_cpp/classes/audio_stream_playback.hpp>
#include <godot_cpp/classes/audio_frame.hpp>

#include "audio_stream_voip.h"


namespace godot {


class AudioStreamPlaybackVOIP : public AudioStreamPlayback {
    GDCLASS(AudioStreamPlaybackVOIP, AudioStreamPlayback)
    friend class AudioStreamVOIP;

private:
    bool active;
    int samples_processed;

protected:
    static void _bind_methods() {}

public:
    const double FRAME_SIZE = 0.02; // in seconds
    const double SAMPLE_RATE = 44100.; // in hz, maybe get this from somewhere else

    Ref<AudioStreamVOIP> base;

    virtual void _start(double p_from_pos = 0.0) override;
    virtual void _stop() override;
    virtual bool _is_playing() const override;
    virtual int32_t _mix(AudioFrame *buffer, double rate_scale, int32_t frames) override;
    
    virtual int _get_loop_count() const override { return 0; }
	virtual double _get_playback_position() const override { return 0; }
	virtual void _seek(double p_time) override {}

};


}

#endif