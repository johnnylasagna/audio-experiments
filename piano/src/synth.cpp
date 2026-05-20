#include "../include/synth.h"

// ---------------------
// ---- Constructor ----
// ---------------------

Synth::Synth() = default;

// ------------------------------
// ---- Oscillator functions ----
// ------------------------------

void Synth::addOscillator(float frequency) {
	oscillators.emplace_back(frequency);
	oscillatorCount++;
}

void Synth::addOscillator(Oscillator oscillator) {
	oscillators.push_back(oscillator);
	oscillatorCount++;
}

void Synth::addOscillator(Oscillator oscillator, ADSR envelope) {
	oscillators.push_back(oscillator);
	oscillators.back().setADSRattributes(envelope);
	oscillatorCount++;
}

// ------------------------
// ---- ADSR functions ----
// ------------------------

void Synth::setADSR(float attackTime, float decayTime, float sustainLevel, float releaseTime) {
	for (auto &oscillator : oscillators) {
		oscillator.setADSRattributes(attackTime, decayTime, sustainLevel, releaseTime);
	}
}

// ------------------------
// ---- Note functions ----
// ------------------------

void Synth::playNote(int note) { oscillators[note].playNote(); }

void Synth::stopNote(int note) { oscillators[note].stopNote(); }

void Synth::setOscillatorType(OscillatorType type) {
	for (auto &oscillator : oscillators) {
		oscillator.setType(type);
	}
}

// --------------------------------
// ---- Audio stream functions ----
// --------------------------------

float Synth::getNextValue() {
	float sample = 0;
	int count = 0;

	for (auto &oscillator : oscillators) {
		if (oscillator.isActive()) {
			count++;
			sample += oscillator.getNextValue();
		}
	}

	if (count > 0) {
		sample /= std::sqrt(static_cast<float>(count));
	}

	return sample * 0.2f;
}