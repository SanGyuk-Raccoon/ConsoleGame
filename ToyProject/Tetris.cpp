#include "UtilModule.h"
#include "Shape.h"
#include "ShapeBuilder.h"
#include "GameBoard.h"
#include "BoardViewer.h"
#include "ShapeHandler.h"
#include "Tetris.h"

void Tetris::init() {
	ConsoleHandler::setFontSize(15, 15);
    ConsoleHandler::setConsoleSize(120, 50);
    ConsoleHandler::setTitle("Tetris");

	BoardViewer board_viewer;
	board_viewer.init();
}

void Tetris::start() {
	Rect rect;


}