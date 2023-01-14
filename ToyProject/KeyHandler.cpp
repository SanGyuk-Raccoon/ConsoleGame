#include "UtilBase.h"
#include "KeyHandler.h"
#include <conio.h>

bool KeyHandler::isValidKey(char& c) {
	switch (static_cast<KeyEnum>(c)) {
	case KeyEnum::ExpandKey:
		c = _getch();
		return true;
	case KeyEnum::SpaceBar: 
		return true;
	case KeyEnum::Enter:
		return true;
	default:
		return false;
	}
}

KeyEnum KeyHandler::getKey() {
	while (true) {
		char c = _getch();
		if (isValidKey(c)) {
			return static_cast<KeyEnum>(c);
		}
	}
}