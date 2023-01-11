#include "UtilBase.h"
#include <windows.h>
#include "ConsoleHandler.h"
#include <stdio.h>

const unsigned int ConsoleHandler::Max_Buffer_Size = 1024;

void ConsoleHandler::setConsoleSize(unsigned int width, unsigned int height) {
	char buf[Max_Buffer_Size] = {};
	int ret = sprintf_s(buf, "mode con: cols=%lu lines=%lu", width, height);
	if (ret < 0) {
		printf("sprintf Error in ConsoleHandler::setConsoleSize");
	}
	system(buf);
}
void ConsoleHandler::setTitle(const char* title) {
	char buf[Max_Buffer_Size] = {};
	int ret = sprintf_s(buf, "title %s", title);
	if (ret < 0) {
		printf("sprintf Error in ConsoleHandler::setConsoleSize");
	}
	system(buf);
}