#include "ConsoleUtils.h"

void SetConsoleOption(const char* title, int width, int height) {
	// ToDo
	//system("title [title]");
	//system("mode con: cols=[width] lines=[height]");
}
void SetCursor(int x, int y) {
	SHORT short_x = (SHORT)x;
	SHORT short_y = (SHORT)y;

	assert(short_x == x && short_y == y);
		
	static HANDLE handle = NULL;

	if (handle == NULL) {
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(handle, { short_x, short_y });
}
void SetCursorVisible(bool visiable) {
	static HANDLE handle = NULL;

	if (handle == NULL) {
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	CONSOLE_CURSOR_INFO console_cursor;
	console_cursor.bVisible = visiable;
	console_cursor.dwSize = 1;
	SetConsoleCursorInfo(handle, &console_cursor);
}
void SetCursorColor(ColorType font_color, ColorType background_color) {
	static HANDLE handle = NULL;

	if (handle == NULL) {
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	SetConsoleTextAttribute(handle, (int)font_color | (int)background_color << 4);
}

void SetCursorTest() {
	SetCursorVisible(false);
	for (int x = 0; x < 10; x++) {
		SetCursorColor((ColorType)x, ColorType::White);
		for (int y = 0; y < 10; y++) {
			SetCursor(x, y);
			printf("%d", y);
		}
	}
	SetCursorColor();
}