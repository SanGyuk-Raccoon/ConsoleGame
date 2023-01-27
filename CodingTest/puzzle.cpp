/* 
	[슬라이딩 숫자 퍼즐 문제]

	문제 설명 : 아래와 같은 3x3 슬라이딩 퍼즐을 맞추는 solve함수를 구현하라.

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

	// 실제 슬라이딩 퍼즐을 생각했을 때, "move" 라는 단어가 정확하진 않지만,
	// "비어있는 칸" 자체를 이동시킨다고 생각하도록 하자.
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

// 작성해야할 함수
void solve(Puzzle& puzzle);

int main() {
	// 문제 풀고 나면 TEST_NUM 늘려보자.
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

// 당연하겠지만, 단순 대입으로 맞추면 안 된다.
void solve(Puzzle& puzzle) {

}
