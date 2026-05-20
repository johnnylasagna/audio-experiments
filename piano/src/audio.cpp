#include "../include/audio.h"

// Cannot be a member function so has to be defined outside the class
void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount) {
	Audio *audio = (Audio *)pDevice->pUserData;
	float *output = (float *)pOutput;

	for (ma_uint32 i = 0; i < frameCount; i++) {
		float sample = audio->getNextValue();

		output[2 * i] = sample;
		output[2 * i + 1] = sample;
	}

	(void)pInput;
}

// ---------------------
// ---- Constructor ----
// ---------------------

Audio::Audio() {
	ma_device_config deviceConfig;
	deviceConfig = ma_device_config_init(ma_device_type_playback);
	deviceConfig.playback.format = AudioConfig::deviceFormat;
	deviceConfig.playback.channels = AudioConfig::deviceChannels;
	deviceConfig.sampleRate = AudioConfig::deviceSampleRate;
	deviceConfig.dataCallback = data_callback;
	deviceConfig.pUserData = this;

	if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
		std::cerr << "Failed to open playback device.\n";
		exit(1);
	}

	std::cout << "Device Name: " << device.playback.name << std::endl;

	if (ma_device_start(&device) != MA_SUCCESS) {
		std::cerr << "Failed to start playback device.\n";
		ma_device_uninit(&device);
		exit(2);
	}

	std::cout << "Playback started" << std::endl;
}

// -------------------------
// ---- Synth Functions ----
// -------------------------

void Audio::addSynth() {
	synths.emplace_back();
	synthCount++;
}

void Audio::addSynth(Synth &synth) {
	synths.push_back(synth);
	synthCount++;
}

// ------------------------
// ---- ADSR Functions ----
// ------------------------

void Audio::setADSR(int synthId, float attackTime, float decayTime, float sustainLevel, float releaseTime) {
	synths[synthId].setADSR(attackTime, decayTime, sustainLevel, releaseTime);
}

// ------------------------
// ---- Note Functions ----
// ------------------------

void Audio::playNote(int synthIndex, int note) { synths[synthIndex].playNote(note); }

void Audio::stopNote(int synthIndex, int note) { synths[synthIndex].stopNote(note); }

void Audio::setOscillatorType(int synthIndex, OscillatorType type) { synths[synthIndex].setOscillatorType(type); }

// --------------------------------
// ---- Audio stream functions ----
// --------------------------------

float Audio::getNextValue() {
	float sample = 0;
	for (auto &synth : synths) {
		sample += synth.getNextValue();
	}
	return sample;
}

// --------------------------
// ---- Audio attributes ----
// --------------------------

int Audio::getSynthCount() { return synthCount; }

// --------------------
// ---- Destructor ----
// --------------------

Audio::~Audio() { ma_device_uninit(&device); }