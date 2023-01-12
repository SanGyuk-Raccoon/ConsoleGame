#include "UtilBase.h"
#include "KeyHandler.h"
#include <conio.h>
#include <stdio.h>

/* 
		How...?
*/

bool KeyHandler::isValidKey(char c) {
	if (c == static_cast<char>(KeyEnum::ExpandKey)) {
		return true;
	}
	//else if (c >= 65 && c <= 90) {
	//	return true;
	//}
	//else if (c >= 97 && c <= 122) {
	//	return true;
	//}

	return false;
}
KeyEnum KeyHandler::getKey() {
	char c = _getch();
	while (isValidKey(c)) {
		if (c == static_cast<char>(KeyEnum::ExpandKey)) {
			c = _getch();
		}
	}

	return static_cast<KeyEnum>(c);
}