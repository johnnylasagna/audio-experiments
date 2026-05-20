#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

#include <array>

#include "miniaudio.h"

namespace AudioConfig {

inline constexpr ma_format deviceFormat = ma_format_f32;
inline constexpr int deviceChannels = 2;
inline constexpr float deviceSampleRate =  44100;

} // namespace AudioConfig

#endif