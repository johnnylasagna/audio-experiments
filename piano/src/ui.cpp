#include "../include/ui.h"

// ----------------------
// ---- Constructors ----
// ----------------------

UI::UI() : UI(1200, 900) {}
UI::UI(int screenWidth_, int screenHeight_) : screenWidth(screenWidth_), screenHeight(screenHeight_) {}

// --------------------------
// ---- raylib Functions ----
// --------------------------

void UI::initialize() {
	InitWindow(screenWidth, screenHeight, "Piano");

	std::string fontPath = std::string(GetApplicationDirectory()) + "../font/font.ttf";
	font = LoadFontEx(fontPath.c_str(), 30, nullptr, 0);

	// SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
	SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
	SetTargetFPS(60);
}

void UI::run() {
	while (!WindowShouldClose()) {

		// Update
		handleKeyPresses();
		handleControlChanges();

		// Draw
		BeginDrawing();
		ClearBackground(BLUE);

		drawKeys();
		drawControls();

		EndDrawing();
	}
}

// --------------------------------
// ---- Key Handling Functions ----
// --------------------------------

void UI::handleKeyPresses() {
	handleKeyNotes();
	handleKeyToggle();
	handleKeyType();
	handleKeyStartNote();
}

// ---------------------------
// ---- Drawing Functions ----
// ---------------------------

void UI::drawKeys() {
	for (int i = 0; i < 12; i++) {
		DrawRectangleLines(i * 100, 600, 100, 300, BLACK);

		if (showKeys) {
			DrawTextCentered(font, mapping[i].label, i * 100 + 50, 850, 30, BLACK);
			DrawTextCentered(font, mapping[i + 12].label, i * 100 + 50, 650, 30, BLACK);
		}

		DrawTextCentered(font, keysNames[i], i * 100 + 50, 750, 30, BLACK);
	}

	DrawTextCentered(font, startNoteText.c_str(), 50, 550, 30, BLACK);
	// DrawTextCentered(font, std::to_string(startingNote).c_str(), 50, 600, 30, BLACK);
}

// ---------------------------
// ---- Control Functions ----
// ---------------------------

void UI::setControls(float attackTime, float decayTime, float sustainLevel, float releaseTime) {
	controls[0] = attackTime;
	controls[1] = decayTime;
	controls[2] = sustainLevel;
	controls[3] = releaseTime;
}

void UI::drawControls() {

	if (showControls) {
		drawADSRcontrols();
		drawWaveControls();
	}
}

void UI::handleControlChanges() {

	static int ADSRstartX = 50;
	static int ADSRstartY = 50;

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();
		float x = mousePos.x - ADSRstartX;
		float y = mousePos.y - ADSRstartY;

		if (y > 300 || y < 0 || x < 0 || x >= 400) {
			return;
		}

		int index = static_cast<int>(x) / 100;

		controls[index] = (300 - y) / 300 * UIconfig::ADSR::controls[index].maxValue;
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();
		float x = mousePos.x - ADSRstartX;
		float y = mousePos.y - ADSRstartY;

		if (0 < x && x < 400 && y < 300) {
			setADSR(0, controls[0], controls[1], controls[2], controls[3]);
		}
	}
}

// --------------------------
// ---- Audio Functions ----
// --------------------------

void UI::setAudio(Audio *audio_) { audio = audio_; }

void UI::setADSR(int synthId, float attackTime, float decayTime, float sustainLevel, float releaseTime) {
	audio->setADSR(synthId, attackTime, decayTime, sustainLevel, releaseTime);
}

// --------------------
// ---- Destructor ----
// --------------------

UI::~UI() {
	if (font.texture.id != 0) {
		UnloadFont(font);
	}
	CloseWindow();
}

// Private Functions

// --------------------------------
// ---- Key Handling Functions ----
// --------------------------------

void UI::handleKeyNotes() {
	for (int i = 0; i < 24; i++) {
		const auto &key = mapping[i];

		const int noteInterval = i % 12;
		const int noteOctave = i / 12;

		const int note = (startingNote + noteInterval + noteOctave * 12);

		if (note < 0 || note > 107) {
			continue;
		}

		if (IsKeyPressed(key.raylibKey)) {
			audio->playNote(0, note);
			// std::cout << "Playing note: " << note << std::endl;
		}

		if (IsKeyReleased(key.raylibKey)) {
			audio->stopNote(0, note);
		}

		if (IsKeyDown(key.raylibKey)) {
			if (i < 12) {
				DrawRectangle(i * 100, 600, 100, 300, RED);
			} else {
				DrawRectangle((i - 12) * 100, 600, 100, 150, YELLOW);
			}
		}

		if (IsKeyUp(key.raylibKey)) {
			if (i < 12) {
				DrawRectangle(i * 100, 600, 100, 300, WHITE);
			}
		}
	}
}

void UI::handleKeyToggle() {
	if (IsKeyPressed(KEY_TAB)) {
		showKeys = !showKeys;

	} else if (IsKeyPressed(KEY_ENTER)) {
		showControls = !showControls;

	} else if (IsKeyPressed(KEY_SPACE)) {
		linearMapping = !linearMapping;
		if (!linearMapping) {
			mapping = UIconfig::mappingsNonLinear;
		} else {
			mapping = UIconfig::mappingsLinear;
		}
	}
}

void UI::handleKeyType() {
	if (IsKeyPressed(KEY_UP)) {
		audio->setOscillatorType(0, OscillatorType::Sine);
		controls[4] = 0;

	} else if (IsKeyPressed(KEY_RIGHT)) {
		audio->setOscillatorType(0, OscillatorType::Triangle);
		controls[4] = 1;

	} else if (IsKeyPressed(KEY_DOWN)) {
		audio->setOscillatorType(0, OscillatorType::Sawtooth);
		controls[4] = 2;

	} else if (IsKeyPressed(KEY_LEFT)) {
		audio->setOscillatorType(0, OscillatorType::Square);
		controls[4] = 3;
	}
}

void UI::handleKeyStartNote() {
	if (IsKeyPressed(KEY_COMMA)) {
		startingNote = std::max(startingNote - 1, 0);
		startNoteText = MusicConfig::NoteNames[startingNote % 12] + std::to_string(startingNote / 12);
	} else if (IsKeyPressed(KEY_PERIOD)) {
		startingNote = std::min(startingNote + 1, 107);
		startNoteText = MusicConfig::NoteNames[startingNote % 12] + std::to_string(startingNote / 12);
	} else if (IsKeyPressed(KEY_SEMICOLON)) {
		startingNote = std::max(startingNote - 12, 0);
		startNoteText = MusicConfig::NoteNames[startingNote % 12] + std::to_string(startingNote / 12);
	} else if (IsKeyPressed(KEY_APOSTROPHE)) {
		startingNote = std::min(startingNote + 12, 107);
		startNoteText = MusicConfig::NoteNames[startingNote % 12] + std::to_string(startingNote / 12);
	}
}

// ---------------------------
// ---- Drawing Functions ----
// ---------------------------

void UI::drawADSRcontrols() {
	for (int i = 0; i < 4; i++) {

		const auto &control = UIconfig::ADSR::controls[i];

		float controlStartPosY =
		    UIconfig::ADSR::startY + UIconfig::ADSR::size - controls[i] / control.maxValue * UIconfig::ADSR::size;
		float controlHeight = controls[i] / control.maxValue * UIconfig::ADSR::size;

		DrawRectangle(control.RectX, controlStartPosY, UIconfig::ADSR::width, controlHeight, control.color);
		DrawRectangleLines(control.RectX, controlStartPosY, UIconfig::ADSR::width, controlHeight, BLACK);

		std::string controlText = std::to_string(controls[i]);

		float ADSRtextY = UIconfig::ADSR::startY + UIconfig::ADSR::size - controlHeight - 20;

		DrawTextCentered(font, controlText.c_str(), control.textX, ADSRtextY, 20, BLACK);
		DrawTextCentered(font, control.name, control.textX, UIconfig::ADSR::labelY, 20, BLACK);
	}
}

void UI::drawWaveControls() {
	for (auto &rect : UIconfig::Wave::rects) {
		DrawRectangle(rect.x, rect.y, rect.width, rect.height, PURPLE);
		DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, BLACK);
	}

	if (controls[4] == 0) {
		DrawTextCentered(font, "Sine", UIconfig::Wave::startX + 100, 200, 25, BLACK);
	} else if (controls[4] == 1) {
		DrawTextCentered(font, "Tri", UIconfig::Wave::startX + 200, 300, 25, BLACK);
	} else if (controls[4] == 2) {
		DrawTextCentered(font, "Saw", UIconfig::Wave::startX + 100, 300, 25, BLACK);
	} else if (controls[4] == 3) {
		DrawTextCentered(font, "Square", UIconfig::Wave::startX, 300, 25, BLACK);
	}
}

void UI::DrawTextCentered(Font font, const char *text, int centerX, int y, int fontSize, Color color) {
	int textWidth;
	int textHeight;

	if (font.texture.id == 0) {
		textWidth = MeasureText(text, fontSize);
	} else {
		textWidth = MeasureTextEx(font, text, fontSize, 1.0f).x;
		textHeight = MeasureTextEx(font, text, fontSize, 1.0f).y;
	}

	if (font.texture.id == 0) {
		DrawText(text, centerX - textWidth / 2, y - fontSize / 2, fontSize, color);
	} else {
		DrawTextEx(font, text, {(float)centerX - textWidth / 2, (float)y - textHeight / 2}, fontSize, 1.0f, color);
	}
}