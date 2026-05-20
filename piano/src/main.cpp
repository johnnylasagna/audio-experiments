// C++ includes
#include <chrono>
#include <conio.h>
#include <iostream>
#include <thread>
#include <vector>

// Miniaudio macros
#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DECODING
#define MA_NO_ENCODING

// Nvidia and AMD GPU support
// extern "C" {
// __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
// __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
// }

// UI has to be included before audio
// to prevent conflicts between raylib and miniaudio
#include "../include/ui.h"

#include "../include/audio.h"
#include "../include/music_config.h"

int main(int argc, char **argv) {

	Synth synth;

	float attackTime = 0.01f;
	float decayTime = 0.3f;
	float sustainLevel = 0.0f;
	float releaseTime = 0.2f;

	// Change later to only add default ADSR;

	ADSR envelope(attackTime, decayTime, sustainLevel, releaseTime);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 12; j++) {
			synth.addOscillator(MusicConfig::noteFrequencies[j][i], envelope);
		}
	}

	Audio audio;
	audio.addSynth(synth);

	UI ui;
	ui.initialize();
	ui.setAudio(&audio);
	ui.setControls(attackTime, decayTime, sustainLevel, releaseTime);
	ui.run();

	(void)argc;
	(void)argv;

	return 0;
}

// ADSR envelope(0.01, 0.3, 0.0, 0.2);
// ADSR envelope(0.3, 0.7, 0.5, 0.4);
// ADSR envelope(1.5, 0.1, 1, 0.1);
// ADSR envelope(0.001, 1, 0.7, 2.0);