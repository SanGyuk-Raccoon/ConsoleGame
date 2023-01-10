#include "UtilModule.h"
#include <stdio.h>

int main() {
	Cursor::getInstance().setPosition(0, 0);
	printf("Cursor");

	Cursor::getInstance().setFontColor(Color::Black, Color::Red);
	Cursor::getInstance().setPosition(0, 1);
	printf("Test");
	
    return 0;
}

