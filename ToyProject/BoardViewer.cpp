#include "UtilModule.h"
#include "Shape.h"
#include "ShapeBuilder.h"
#include "GameBoard.h"
#include "BoardViewer.h"
#include <stdio.h>

constexpr Uint8 LEFT_WHITE = 6;
constexpr Uint8 UPPER_WHITE = 3;

void BoardViewer::init() {
	// ToDo : 기본 게임판 및 우측 다음 블락 그려줄 네모칸 그리기
	Cursor::getInstance().setFontColor(Color::Gray);

	for (Uint8 x = 1; x <= BOARD_WIDTH; x++) {
		Cursor::getInstance().setPosition(2 * x + LEFT_WHITE, 0 + UPPER_WHITE);
		printf("■");
	}
	for (Uint8 x = 1; x <= BOARD_WIDTH; x++) {
		Cursor::getInstance().setPosition(2 * x + LEFT_WHITE, BOARD_HEIGHT + UPPER_WHITE + 1);
		printf("■");
	}
	for (Uint8 y = 1; y <= BOARD_HEIGHT; y++) {
		Cursor::getInstance().setPosition(LEFT_WHITE, y + UPPER_WHITE);
		printf("■");
	}
	for (Uint8 y = 1; y <= BOARD_HEIGHT; y++) {
		Cursor::getInstance().setPosition(LEFT_WHITE + 2 * (BOARD_WIDTH+1), y + UPPER_WHITE);
		printf("■");
	}
}