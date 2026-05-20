#ifndef OSCILLATOR_CONFIG_H
#define OSCILLATOR_CONFIG_H

#include <array>
#include <cmath>

namespace OscillatorConfig {

inline constexpr int tableSize = 1024;
inline constexpr float Pi = 3.14159265358979323846f;

inline const std::array<float, OscillatorConfig::tableSize> sineTable = [] {
	std::array<float, OscillatorConfig::tableSize> table{};

	for (int i = 0; i < OscillatorConfig::tableSize; i++) {
		table[i] = sinf((2.0f * OscillatorConfig::Pi * i) / OscillatorConfig::tableSize);
	}
	return table;
}();

} // namespace OscillatorConfig

#endif