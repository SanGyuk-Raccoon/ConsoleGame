/* 
	[�����̵� ���� ���� ����]

	���� ���� : �Ʒ��� ���� 3x3 �����̵� ������ ���ߴ� solve�Լ��� �����϶�.

			y
			0  1  2
		   ---------
	x   0 | 1  2  3
		1 | 4  5  6
		2 | 7  8  0
*/

#define TEST_NUM (10)

#include <stdio.h>
#include <random>
#include <time.h>

enum class Direction : unsigned char {
	Left = 0,
	Right,
	Up,
	Down,
	Max
};

struct Puzzle {
	unsigned int puzzle[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	unsigned int x = 2, y = 2;

	bool isCorrect() {
		constexpr unsigned int ANSWER[3][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
		return memcmp(puzzle, ANSWER, 3 * 3 * sizeof(unsigned int)) == 0;
	}

	// ���� �����̵� ������ �������� ��, "move" ��� �ܾ ��Ȯ���� ������,
	// "����ִ� ĭ" ��ü�� �̵���Ų�ٰ� �����ϵ��� ����.
	void move(Direction dir) {
		unsigned int temp;
		switch (dir) {
		case Direction::Left:
			if (y > 0) {
				puzzle[x][y] = puzzle[x][y - 1];
				y--;
				puzzle[x][y] = 0;
			}
			return;
		case Direction::Right:
			if (y < 2) {
				puzzle[x][y] = puzzle[x][y + 1];
				y++;
				puzzle[x][y] = 0;
			}
			return;
		case Direction::Up:
			if (x > 0) {
				puzzle[x][y] = puzzle[x - 1][y];
				x--;
				puzzle[x][y] = 0;
			}
			return;
		case Direction::Down:
			if (x < 2) {
				puzzle[x][y] = puzzle[x + 1][y];
				x++;
				puzzle[x][y] = 0;
			}
		}
	}
};

int generateRandomInt(int min, int max);
void shuffle(Puzzle& puzzle);

// �ۼ��ؾ��� �Լ�
void solve(Puzzle& puzzle);

int main() {
	// ���� Ǯ�� ���� TEST_NUM �÷�����.
	for (int i = 0; i < TEST_NUM; i++) {
		Puzzle puzzle;
		shuffle(puzzle);
		clock_t start = clock();
		solve(puzzle);
		clock_t running_time = clock() - start;
		if (puzzle.isCorrect()) {
			printf("%d Answer is Correct.(time:%lu)\n", i, (unsigned int)running_time);
		}
		else {
			printf("%d Answer is NOT Correct.\n", i);
		}
	}

	return 0;
}

//
int generateRandomInt(int min, int max) {
	static std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

void shuffle(Puzzle& puzzle) {
	constexpr unsigned int shuffle_count = 500;
	for (unsigned int  i = 0; i < shuffle_count; i++) {
		Direction dir = static_cast<Direction>(generateRandomInt(0, 3));
		puzzle.move(dir);
	}
}

// �翬�ϰ�����, �ܼ� �������� ���߸� �� �ȴ�.
void solve(Puzzle& puzzle) {

}
