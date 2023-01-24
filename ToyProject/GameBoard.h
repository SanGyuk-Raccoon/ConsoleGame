constexpr Uint32 BOARD_HEIGHT = 40;
constexpr Uint32 BOARD_WIDTH = 25;

class GameBoard {
private:
	// 도형마다 다른 색깔로 칠해주면 어떨까?
	Color Board[BOARD_HEIGHT][BOARD_WIDTH];
public:
	void setBoard(Uint32 x, Uint32 y, Color color);
};
