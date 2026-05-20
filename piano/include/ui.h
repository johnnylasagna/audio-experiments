#ifndef UI_H
#define UI_H

// These defines are to prevent conflicts
// with the win32 API included in miniaudio
// and raylib's own functions
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER

// raylib MUST be included before miniaudio
// to prevent any form of conflicts
#include <array>
#include <filesystem>

#include <raylib.h>

#include "audio.h"
#include "ui_config.h"
#include "music_config.h"

class UI {
	int screenWidth;
	int screenHeight;

	Audio *audio = nullptr;

	std::array<float, 5> controls{};

	bool showKeys = false;
	bool showControls = true;
	bool linearMapping = true;

	Font font{};

	static constexpr std::array<const char *, 12> keysNames = {"I",   "bII", "II", "bIII", "III",  "IV",
	                                                           "#IV", "V",   "#V", "VI",   "bVII", "VII"};

	const std::array<UIconfig::KeyMapping, 24> *mapping = &UIconfig::mappingsLinear;

	int startingNote = 48;
	std::string startNoteText = MusicConfig::NoteNames[startingNote % 12] + std::to_string(startingNote / 12);

	// Key handling functions
	void handleKeyNotes();
	void handleKeyToggle();
	void handleKeyType();
	void handleKeyStartNote();

	// Drawing functions
	void drawADSRcontrols();
	void drawWaveControls();
	void DrawTextCentered(Font font, const char *text, int centerX, int y, int fontSize, Color color);

  public:
	// Constuctors
	UI();
	UI(int screenWidth_, int screenHeight_);

	// raylib functions
	void initialize();
	void run();

	// Key handling functions
	void handleKeyPresses();

	// Drawing functions
	void drawKeys();

	// Control functions
	void setControls(float attackTime, float decayTime, float sustainLevel, float releaseTime);
	void drawControls();
	void handleControlChanges();

	// Audio functions
	void setAudio(Audio *audio_);
	void setADSR(int synthId, float attackTime, float decayTime, float sustainLevel, float releaseTime);

	// Destructor
	~UI();
};

#endif