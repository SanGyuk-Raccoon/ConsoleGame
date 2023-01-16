#include "UtilModule.h"
#include "Shape.h"
#include "ShapeHandler.h"
void ShapeHandler::move(KeyEnum key) {
	switch (key) {
	case KeyEnum::Down:
		moveDown();
		return;
	case KeyEnum::Left:
		moveLeft();
		return;
	case KeyEnum::Right:
		moveRight();
		return;
	case KeyEnum::SpaceBar:
		moveSpaceBar();
		return;
	}
}

void ShapeHandler::moveDown() {}
void ShapeHandler::moveLeft() {}
void ShapeHandler::moveRight() {}
void ShapeHandler::moveSpaceBar() {}