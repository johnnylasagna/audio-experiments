#include "../include/oscillator.h"

// ----------------------
// ---- Constructors ----
// ----------------------

Oscillator::Oscillator(float frequency_) : frequency(frequency_) {
	phaseIncrement = frequency * (float)OscillatorConfig::tableSize / AudioConfig::deviceSampleRate;
}

Oscillator::Oscillator(float frequency_, ADSR envelope_) : frequency(frequency_), envelope(envelope_) {
	phaseIncrement = frequency * (float)OscillatorConfig::tableSize / AudioConfig::deviceSampleRate;
}

// ------------------------
// ---- ADSR Functions ----
// ------------------------

void Oscillator::setADSRattributes(float attackTime, float decayTime, float sustainLevel, float releaseTime) {
	envelope.setAttributes(attackTime, decayTime, sustainLevel, releaseTime);
}

void Oscillator::setADSRattributes(ADSR envelope_) { envelope = envelope_; }

// ------------------------
// ---- Note Functions ----
// ------------------------

void Oscillator::playNote() { envelope.noteOn(); }

void Oscillator::stopNote() { envelope.noteOff(); }

// --------------------------------
// ---- Audio stream Functions ----
// --------------------------------

float Oscillator::getNextValue() {

	float sample = 0.0f;

	switch (type) {
	case OscillatorType::Sine:
		sample = getSineSample();
		break;
	case OscillatorType::Square:
		sample = getSquareSample();
		break;
	case OscillatorType::Sawtooth:
		sample = getSawtoothSample();
		break;
	case OscillatorType::Triangle:
		sample = getTriangleSample();
		break;
	default:
		break;
	}

	float amplitude = envelope.process();

	phase += phaseIncrement;
	if (phase >= OscillatorConfig::tableSize) {
		phase -= OscillatorConfig::tableSize;
	}

	return sample * amplitude;
}

// -------------------------------
// ---- Oscillator attributes ----
// -------------------------------

void Oscillator::setFrequency(int newFreq) {
	frequency = newFreq;
	phaseIncrement = frequency * (float)OscillatorConfig::tableSize / AudioConfig::deviceSampleRate;
}

bool Oscillator::isActive() { return (envelope.isStageOff()) ? false : true; }

void Oscillator::setType(OscillatorType newType) { type = newType; }

// Private Functions

// ---------------------------------------
// ---- Oscillator waveform functions ----
// ---------------------------------------

float Oscillator::getSineSample() {
	int phaseIndex = (int)phase;
	float phaseFraction = phase - phaseIndex;

	phaseIndex = phaseIndex % OscillatorConfig::tableSize;

	float sample1 = OscillatorConfig::sineTable[phaseIndex];
	float sample2 = OscillatorConfig::sineTable[(phaseIndex + 1) % OscillatorConfig::tableSize];

	return sample1 + (sample2 - sample1) * phaseFraction;
}

float Oscillator::getSquareSample() { return (phase < OscillatorConfig::tableSize / 2) ? 1.0f : -1.0f; }

float Oscillator::getSawtoothSample() { return (phase / OscillatorConfig::tableSize) * 2.0f - 1.0f; }

float Oscillator::getTriangleSample() {
	float normalized = phase / OscillatorConfig::tableSize;
	float sample = 4.0f * fabsf(normalized - 0.5f) - 1.0f;

	return sample;
}
