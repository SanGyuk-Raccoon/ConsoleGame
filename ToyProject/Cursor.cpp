#include "UtilBase.h"
#include <windows.h>
#include "ConsoleHandler.h"
#include "Cursor.h"

void Cursor::setVisibleOption(bool visiable) {
	CONSOLE_CURSOR_INFO console_cursor;
	console_cursor.bVisible = visiable;
	console_cursor.dwSize = 1;
	SetConsoleCursorInfo(ConsoleHandler::getHandle(), &console_cursor);
}
void Cursor::setPosition(unsigned int x, unsigned int y) {
	SetConsoleCursorPosition(ConsoleHandler::getHandle(), { (short)x, (short)y });
}
void Cursor::setFontColor(Color font_color, Color background_color) {
	SetConsoleTextAttribute(ConsoleHandler::getHandle(), (int)font_color | (int)background_color << 4);
}