#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <array>
#include <raylib.h>

namespace UIconfig {

inline constexpr int screenWidth = 1200;
inline constexpr int screenHeight = 900;

struct KeyMapping {
	int raylibKey;
	const char *label;
};

inline constexpr std::array<KeyMapping, 24> mappingsNonLinear = {
    {{KEY_Z, "Z"},   {KEY_S, "S"},     {KEY_X, "X"},     {KEY_D, "D"},    {KEY_C, "C"},     {KEY_V, "V"},
     {KEY_G, "G"},   {KEY_B, "B"},     {KEY_H, "H"},     {KEY_N, "N"},    {KEY_J, "J"},     {KEY_M, "M"},

     {KEY_W, "W"},   {KEY_THREE, "3"}, {KEY_E, "E"},     {KEY_FOUR, "4"}, {KEY_R, "R"},     {KEY_T, "T"},
     {KEY_SIX, "6"}, {KEY_Y, "Y"},     {KEY_SEVEN, "7"}, {KEY_U, "U"},    {KEY_EIGHT, "8"}, {KEY_I, "I"}}};

inline constexpr std::array<KeyMapping, 24> mappingsLinear = {{{KEY_Q, "Q"},
                                                               {KEY_W, "W"},
                                                               {KEY_E, "E"},
                                                               {KEY_R, "R"},
                                                               {KEY_T, "T"},
                                                               {KEY_Y, "Y"},
                                                               {KEY_U, "U"},
                                                               {KEY_I, "I"},
                                                               {KEY_O, "O"},
                                                               {KEY_P, "P"},
                                                               {KEY_LEFT_BRACKET, "["},
                                                               {KEY_RIGHT_BRACKET, "]"},
                                                               {KEY_ONE, "1"},
                                                               {KEY_TWO, "2"},
                                                               {KEY_THREE, "3"},
                                                               {KEY_FOUR, "4"},
                                                               {KEY_FIVE, "5"},
                                                               {KEY_SIX, "6"},
                                                               {KEY_SEVEN, "7"},
                                                               {KEY_EIGHT, "8"},
                                                               {KEY_NINE, "9"},
                                                               {KEY_ZERO, "0"},
                                                               {KEY_MINUS, "-"},
                                                               {KEY_EQUAL, "="}}};
;

namespace ADSR {

struct Control {
	const char *name;
	float maxValue;
	float RectX;
	float textX;
	Color color;
};

constexpr float size = 300.0f;
constexpr float width = 100.0f;

constexpr float startX = 50.0f;
constexpr float startY = 50.0f;

constexpr float labelY = startY + size + 20;

inline constexpr std::array<Control, 4> controls = {
    {{"Attack", 5.0f, startX, startX + width / 2, RED},
     {"Decay", 5.0f, startX + width, startX + 3 * width / 2, ORANGE},
     {"Sustain", 1.0f, startX + 2 * width, startX + 5 * width / 2, YELLOW},
     {"Release", 5.0f, startX + 3 * width, startX + 7 * width / 2, GREEN}}};

} // namespace ADSR

namespace Wave {

constexpr float size = 100.0f;
constexpr float startX = 800.0f;
constexpr float startY = 100.0f;

inline constexpr std::array<Rectangle, 4> rects = {{{startX + size * 0.5f, startY + size * 0.5f, size, size},
                                                    {startX - size * 0.5f, startY + size * 1.5f, size, size},
                                                    {startX + size * 0.5f, startY + size * 1.5f, size, size},
                                                    {startX + size * 1.5f, startY + size * 1.5f, size, size}}};
} // namespace Wave

} // namespace UIconfig

#endif