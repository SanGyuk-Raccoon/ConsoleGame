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

/* 위는 건들이지 말고, 아래부터 구현하면 된다. */

using PuzzleKey = unsigned long long int;

// move history는 사용하지 않았음.
// 이후에 개선시킬 풀이에 사용 예정.
struct MovingHistory {
	// 2 bit per each history
	// 8 byte = 32 history
	unsigned long long int history;
	unsigned char count;
	MovingHistory() : history(0), count(0) {}
	void addHistory(Direction dir) {
		count++;
		history <<= 2;
		history += static_cast<unsigned char>(dir);
	}
};

struct HashNode {
	PuzzleKey key;
	HashNode* next;
	HashNode() : key(0), next(nullptr) {}
};

struct HashNodeAllocator {
	// static 으로 되어 있어서 재활용할 때, 이전 값이 있을 수 있음. 사용처에서 memcpy 범위 제대로 정의해줄 것.
	static HashNode node_pool[362880]; // 9! = 362880
	static unsigned int index;
	static HashNode* allcate() {
		return &node_pool[index++];
	}
};
unsigned int HashNodeAllocator::index = 0;
HashNode HashNodeAllocator::node_pool[362880];

class HashSet {
private:
	static constexpr unsigned int BUCKET_SIZE = 9876;

	static inline unsigned int hash_function(unsigned long long int puzzle_key) {
		return puzzle_key % BUCKET_SIZE;
	}

	static HashNode* _bucket[BUCKET_SIZE];

public:
	static void clear() { memset(_bucket, 0, BUCKET_SIZE * sizeof(HashNode*)); }
	static bool add(PuzzleKey key) {
		unsigned int hash = hash_function(key);
		HashNode* head = _bucket[hash];
		HashNode* prev = nullptr;
		while (head) {
			if (head->key == key) {
				return false;
			}
			prev = head;
			head = head->next;
		}

		HashNode* new_node = HashNodeAllocator::allcate();
		new_node->next = nullptr;
		new_node->key = key;
		if (prev == nullptr) {
			_bucket[hash] = new_node;
		}
		else {
			prev->next = new_node;
		}
		return true;
	}
};
HashNode* HashSet::_bucket[BUCKET_SIZE];

struct KeyQueue {
	static PuzzleKey key_queue[300000];
	static unsigned int write_point;
	static unsigned int read_point;
};
PuzzleKey KeyQueue::key_queue[300000];
unsigned int KeyQueue::write_point = 0;
unsigned int KeyQueue::read_point = 0;

inline PuzzleKey getPuzzleKey(Puzzle& puzzle) {
	PuzzleKey key(0);
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			key <<= 4;
			key += puzzle.puzzle[x][y];
		}
	}
	return key;
}

inline void decodePuzzleKey(Puzzle& puzzle, PuzzleKey key) {
	for (int x = 2; x >= 0; x--) {
		for (int y = 2; y >= 0; y--) {
			unsigned int value = key & 0b1111;
			if (value == 0) {
				puzzle.x = x;
				puzzle.y = y;
			}
			puzzle.puzzle[x][y] = value;
			key >>= 4;
		}
	}
}

void init() {
	KeyQueue::write_point = 0;
	KeyQueue::read_point = 0;
	HashNodeAllocator::index = 0;
	HashSet::clear();
}

inline void addCandidate(PuzzleKey key) {
	if (HashSet::add(key)) {
		KeyQueue::key_queue[KeyQueue::write_point++] = key;
	}
}

inline PuzzleKey& getCandidate() {
	return KeyQueue::key_queue[KeyQueue::read_point++];
}
void solve(Puzzle& puzzle) {
	// clear All DataStructure
	init();

	// input first candidate
	{
		PuzzleKey key = getPuzzleKey(puzzle);
		addCandidate(key);
	}
	
	// solve by BFS
	while (true) {
		PuzzleKey& candidate_key = getCandidate();
		Puzzle candidate_puzzle;
		decodePuzzleKey(candidate_puzzle, candidate_key);
		
		if (candidate_puzzle.isCorrect()) {
			puzzle = candidate_puzzle;
			return;
		}
		else {
			for (char dir = 0; dir < 4; dir++) {
				Puzzle temp = candidate_puzzle;
				temp.move(static_cast<Direction>(dir));
				addCandidate(getPuzzleKey(temp));
			}
		}
	}
}
