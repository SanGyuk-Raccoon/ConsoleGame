#include "UtilModule.h"
#include "Shape.h"
#include "ShapeBuilder.h"
#include "GameBoard.h"
#include "BoardViewer.h"
#include "ShapeHandler.h"

ShapeHandler::ShapeHandler() {
	move_func[(Uint8)KeyEnum::Left] = &ShapeHandler::moveLeft;
	move_func[(Uint8)KeyEnum::Right] = &ShapeHandler::moveRight;
	move_func[(Uint8)KeyEnum::SpaceBar] = &ShapeHandler::moveSpaceBar;
	move_func[(Uint8)KeyEnum::Down] = &ShapeHandler::moveDown;
}

void ShapeHandler::moveDown() {}
void ShapeHandler::moveLeft() {}
void ShapeHandler::moveRight() {}
void ShapeHandler::moveSpaceBar() {}

void ShapeHandler::move(KeyEnum key) {
	(this->*move_func[(Uint8)key])();
}

void ShapeHandler::setShape(IShape* shape) {
	this->shape = shape;
}