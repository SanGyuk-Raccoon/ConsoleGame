#include "UtilModule.h"
#include "Shape.h"

Rect::Rect() {
	color = Color::Red;
	for (Uint32 i = 0; i < 2; i++) {
		for (Uint32 j = 0; j < 2; j++) {
			shape[i][j] = true;
		}
	}
}