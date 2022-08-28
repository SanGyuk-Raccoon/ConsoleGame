#pragma once
#include <windows.h>

enum class ColorType {
	Black = 0, DarkBlue, DarkGreen, DarkSky, DarkRed, DarkYellow, DarkPurple, 
	Gray, DarkGray, Blue, Green, Sky, Red, Purple, Yellow, White
};

void SetConsoleOption(const char* title, int width, int height);
void SetCursor(int x, int y);
void SetCursorVisible(bool visiable);
void SetCursorColor(ColorType font_color = ColorType::Gray, ColorType background_color = ColorType::Black);