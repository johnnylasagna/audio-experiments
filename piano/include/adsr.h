#ifndef ADSR_H
#define ADSR_H

#include <iostream>

#include "audio_config.h"

enum class EnvelopeStage { Attack, Decay, Sustain, Release, Off };

class ADSR {
	float amplitude = 0.0f;
	float attackTime;
	float decayTime;
	float sustainLevel;
	float releaseTime;
	float releaseStartAmplitude;

	EnvelopeStage stage = EnvelopeStage::Off;

	// ADSR processing functions
	void processAttack();
	void processDecay();
	void processRelease();
	void processSustain();

  public:
	// Constructors
	ADSR();
	ADSR(float a, float d, float s, float r);

	// ADSR functions
	void setAttributes(float a, float d, float s, float r);

	// Note functions
	void noteOn();
	void noteOff();

	// Audio stream functions
	float process();

	// ADSR attributes
	bool isStageOff();
};

#endif // ADSR_H