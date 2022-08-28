#include "ConsoleUtils.h"
#include <stdio.h>

int main() {
	SetCursorVisible(false);
	SetCursorColor(ColorType::Black, ColorType::White);
	SetCursor(1, 1);
	printf("o");
	SetCursorColor();

    return 0;
}

