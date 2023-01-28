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

/* ���� �ǵ����� ����, �Ʒ����� �����ϸ� �ȴ�. */

using PuzzleKey = unsigned long long int;

// move history�� ������� �ʾ���.
// ���Ŀ� ������ų Ǯ�̿� ��� ����.
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
	// static ���� �Ǿ� �־ ��Ȱ���� ��, ���� ���� ���� �� ����. ���ó���� memcpy ���� ����� �������� ��.
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
