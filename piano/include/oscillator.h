#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <array>
#include <cmath>
#include <iostream>

#include "adsr.h"
#include "audio_config.h"
#include "oscillator_config.h"

enum class OscillatorType { Sine, Square, Sawtooth, Triangle };

class Oscillator {
	float phase = 0;
	float frequency;
	float phaseIncrement;

	OscillatorType type = OscillatorType::Sine;
	ADSR envelope;

	float getSineSample();
	float getSquareSample();
	float getSawtoothSample();
	float getTriangleSample();

  public:
	// Constructors
	Oscillator(float frequency_);
	Oscillator(float frequency_, ADSR envelope_);

	// ADSR functions
	void setADSRattributes(float attackTime, float decayTime, float sustainLevel, float releaseTime);
	void setADSRattributes(ADSR envelope_);

	// Note functions
	void playNote();
	void stopNote();

	// Audio stream functions
	float getNextValue();

	// Oscillator attributes
	bool isActive();
	void setFrequency(float newFreq);
	void setType(OscillatorType type);
};

#endif // OSCILLATOR_H