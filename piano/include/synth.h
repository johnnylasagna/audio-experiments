#ifndef SYNTH_H
#define SYNTH_H

#include <vector>

#include "oscillator.h"

class Synth {
	std::vector<Oscillator> oscillators;
	int oscillatorCount = 0;

  public:
	// Constructor
	Synth();

	// Oscillator functions
	void addOscillator(float frequency);
	void addOscillator(Oscillator oscillator);
	void addOscillator(Oscillator oscillator, ADSR envelope);

	// ADSR functions
	void setADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime);

	// Note functions
	void playNote(int note);
	void stopNote(int note);
	void setOscillatorType(OscillatorType type);

	// Audio stream functions
	float getNextValue();
};

#endif // SYNTH_H