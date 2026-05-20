#include "../include/adsr.h"

// ----------------------
// ---- Constructors ----
// ----------------------

ADSR::ADSR() = default;

ADSR::ADSR(float attackTime_, float decayTime_, float sustainLevel_, float releaseTime_)
    : attackTime(attackTime_), decayTime(decayTime_), sustainLevel(sustainLevel_), releaseTime(releaseTime_) {}

// ------------------------
// ---- ADSR functions ----
// ------------------------

void ADSR::setAttributes(float attackTime_, float decayTime_, float sustainLevel_, float releaseTime_) {
	attackTime = attackTime_;
	decayTime = decayTime_;
	sustainLevel = sustainLevel_;
	releaseTime = releaseTime_;
}

// ------------------------
// ---- Note functions ----
// ------------------------

void ADSR::noteOn() { stage = EnvelopeStage::Attack; }

void ADSR::noteOff() {
	stage = EnvelopeStage::Release;
	releaseStartAmplitude = amplitude;
}

// -----------------------------------
// ---- Audio stream functions ----
// -----------------------------------

float ADSR::process() {
	switch (stage) {

	case EnvelopeStage::Attack:
		processAttack();
		break;

	case EnvelopeStage::Decay:
		processDecay();
		break;

	case EnvelopeStage::Sustain:
		processSustain();
		break;

	case EnvelopeStage::Release:
		processRelease();
		break;

	case EnvelopeStage::Off:
		amplitude = 0.0f;
		break;
	}

	return amplitude;
}

// -------------------------
// ---- ADSR attributes ----
// -------------------------

bool ADSR::isStageOff() { return (stage == EnvelopeStage::Off); }

// Private functions

// -----------------------------------
// ---- ADSR processing functions ----
// -----------------------------------

void ADSR::processAttack() {
	amplitude += 1.0f / (attackTime * AudioConfig::deviceSampleRate);

	if (amplitude >= 1.0f) {
		amplitude = 1.0f;
		stage = EnvelopeStage::Decay;
	}
}

void ADSR::processDecay() {
	amplitude -= (1.0f - sustainLevel) / (decayTime * AudioConfig::deviceSampleRate);

	if (amplitude <= sustainLevel) {
		amplitude = sustainLevel;
		stage = EnvelopeStage::Sustain;
	}
}

void ADSR::processSustain() {
	// amplitude remains constant during sustain
}

void ADSR::processRelease() {
	amplitude -= releaseStartAmplitude / (releaseTime * AudioConfig::deviceSampleRate);

	if (amplitude <= 0.0f) {
		amplitude = 0.0f;
		stage = EnvelopeStage::Off;
	}
}
