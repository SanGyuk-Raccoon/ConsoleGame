constexpr Uint32 BOARD_HEIGHT = 120;
constexpr Uint32 BOARD_WIDTH = 40;

class GameBoard {
private:
	// �������� �ٸ� ����� ĥ���ָ� ���?
	Color Board[BOARD_HEIGHT][BOARD_WIDTH];
public:
	void setBoard(Uint32 x, Uint32 y, Color color);
};
