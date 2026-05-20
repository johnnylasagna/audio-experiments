#ifndef AUDIO_H
#define AUDIO_H

#include <vector>

#include "synth.h"

// Miniaudio library include
#include "../include/miniaudio.h"

#include "../include/audio_config.h"

class Audio {

	ma_device device;
	std::vector<Synth> synths;
	int synthCount = 0;

  public:
	// Constructor
	Audio();

	// Synth functions
	void addSynth();
	void addSynth(Synth &synth);

	// ADSR functions
	void setADSR(int synthId, float attackTime, float decayTime, float sustainLevel, float releaseTime);

	// Note functions
	void playNote(int synthIndex, int noteIndex);
	void stopNote(int synthIndex, int noteIndex);
	void setOscillatorType(int synthIndex, OscillatorType type);

	// Audio stream functions
	float getNextValue();

	// Audio attributes
	int getSynthCount();

	~Audio();
};

#endif