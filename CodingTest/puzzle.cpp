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

#define TEST_NUM (30)

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
	for (unsigned int i = 0; i < shuffle_count; i++) {
		Direction dir = static_cast<Direction>(generateRandomInt(0, 3));
		puzzle.move(dir);
	}
}

/* ���� �ǵ����� ����, �Ʒ����� �����ϸ� �ȴ�. */

/*
   Ǯ�� ���̵��

   123
   456
   780

   ���� ���¿��� bfs�� ��� ����� ���� hash�� �����Ѵ�.
   �� ��, (���� -> �ش� ���̽�)�� �̵� ����� �Բ� �����Ѵ�.
   ������ ���� ���̽��� �ش� hash�� �翬�� ���� ���̰�, �̵� ��� �ݴ�� �̵���Ű�� �ȴ�.

   Q1)
   solve������ ��, ���� ��� �� ����� ���� �ʿ����, bfs�� �ϸ鼭 ���� ��Ȳ�� ���ö������� ã�´�.

   Q2)
   �ش� Hash�� static���� �����ϸ�, Test Case�� �ݺ��ʿ� ���� ��� ������ ���� �������� �˼��ִ�.
   (��ġ �н��ϴ� ��ó��)

   Q3)
   static�� �����ڸ� Ȱ���ؼ� solve�Լ��� ���۵Ǳ� ��, ���α׷��� ���۵��ڸ��� ��� �������� ã�� ���·� �Ҽ�������?
   �ణ cheating���� �����̱��ѵ� �������� �ñ�
*/
/*
   PuzzleKey

   9�ڸ� Puzzle�� �ѹ��� ���ϱ� ���� long long �� bit�� ����� ���.
   0~8 �̹Ƿ� �ִ� 4bit�� �ʿ��ϰ�, �� 9�ڸ��̱� ������ 36bit�� �ʿ���.
   ����, 64bit�� unsigned long long int �� Key �ڷ������� �����.
*/
using PuzzleKey = unsigned long long int;

/*
   MovingHistory

   �̵��ߴ� ���

   ���ۿ��� 3x3 �����̵� ������ �ִ� 31������ Ǯ���ִٰ� �ϴµ� �ֱ׷��� �ƽôº�??
*/
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
	inline Direction getRecentMove() {
		Direction recent_dir = static_cast<Direction>(history & 0b11);
		history >>= 2;
		count--;
		return recent_dir;
	}
	inline bool isEmpty() {
		return count == 0;
	}
};

struct HashNode {
	PuzzleKey key;
	MovingHistory moving_history;
	HashNode* next;
	HashNode() : key(0), moving_history(), next(nullptr) {}
};

static constexpr unsigned int NODE_COUNT = 362880;
class NodeAllocator {
private:
	static HashNode _node_pool[NODE_COUNT];
	static unsigned int _answer_index;
public:
	static inline HashNode* allocate() {
		return &_node_pool[_answer_index++];
	}
};
HashNode NodeAllocator::_node_pool[NODE_COUNT];
unsigned int NodeAllocator::_answer_index = 0;

class HashMap {
private:
	static constexpr unsigned int BUCKET_SIZE = 100001;

	inline unsigned int hash_func(PuzzleKey key) {
		return key % BUCKET_SIZE;
	}

	HashNode* _bucket[BUCKET_SIZE];
public:
	HashMap() {
		memset(_bucket, 0, sizeof(HashNode*) * BUCKET_SIZE);
	}
	~HashMap() {}

	bool add(PuzzleKey& key, MovingHistory& moving_history) {
		unsigned int hash = hash_func(key);
		HashNode* head = _bucket[hash];
		HashNode* prev = nullptr;
		while (head) {
			if (head->key == key) {
				return false;
			}
			prev = head;
			head = head->next;
		}

		HashNode* new_node = NodeAllocator::allocate();
		//memcpy(&new_node->key, &key, sizeof(PuzzleKey));
		new_node->key = key;
		new_node->moving_history = moving_history;
		if (prev) {
			prev->next = new_node;
		}
		else {
			_bucket[hash] = new_node;
		}
		return true;
	}

	bool find(PuzzleKey key, MovingHistory& moving_history) {
		unsigned int hash = hash_func(key);
		HashNode* head = _bucket[hash];
		HashNode* prev = nullptr;
		while (head) {
			if (head->key == key) {
				moving_history = head->moving_history;
				return true;
			}
			prev = head;
			head = head->next;
		}
		return false;
	}
};

class CandidateQueue {
	PuzzleKey _candidate_key[NODE_COUNT];
	MovingHistory _candidate_history[NODE_COUNT];

	unsigned int _read_point, _write_point;

public:
	inline void addCandidate(PuzzleKey& key, MovingHistory& history) {
		_candidate_key[_write_point] = key;
		_candidate_history[_write_point] = history;
		_write_point++;
	}
	inline void getCandidate(PuzzleKey& ret_key, MovingHistory& ret_history) {
		ret_key = _candidate_key[_read_point];
		ret_history = _candidate_history[_read_point];
		_read_point++;
	}
	inline bool isEmpty() {
		return _read_point == _write_point;
	}
};

PuzzleKey getPuzzleKey(Puzzle& puzzle) {
	PuzzleKey key(0);
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			key <<= 4;
			key += puzzle.puzzle[x][y];
		}
	}
	return key;
}
void decodePuzzleKey(PuzzleKey key, Puzzle& ret_puzzle) {
	for (int x = 2; x >= 0; x--) {
		for (int y = 2; y >= 0; y--) {
			unsigned int value = key & 0xf;
			key >>= 4;
			ret_puzzle.puzzle[x][y] = value;
			if (value == 0) {
				ret_puzzle.x = x;
				ret_puzzle.y = y;
			}
		}
	}
}
void solveImp(Puzzle& problem_puzzle, MovingHistory& moving_history) {
	while (!moving_history.isEmpty()) {
		Direction recent_dir = moving_history.getRecentMove();
		switch (recent_dir) {
		case Direction::Left:
			problem_puzzle.move(Direction::Right);
			break;
		case Direction::Right:
			problem_puzzle.move(Direction::Left);
			break;
		case Direction::Up:
			problem_puzzle.move(Direction::Down);
			break;
		case Direction::Down:
			problem_puzzle.move(Direction::Up);
			break;
		}
	}
}

void solve(Puzzle& puzzle) {
	static bool initialized = false;
	static HashMap answer_hash_map;
	static CandidateQueue candidate_queue;

	// initialized
	if (!initialized) {
		initialized = true;
		Puzzle default_puzzle;
		PuzzleKey default_key = getPuzzleKey(default_puzzle);
		MovingHistory default_history;
		answer_hash_map.add(default_key, default_history);
		candidate_queue.addCandidate(default_key, default_history);
	}

	// find Answer
	PuzzleKey problem_key = getPuzzleKey(puzzle);
	MovingHistory moving_history;
	// #1 ã�Ƴ��� �� �߿� �̹� ������ �ִ��� Ȯ��
	if (!answer_hash_map.find(problem_key, moving_history)) {
		// #2 ������ ã�� �� �����ٸ�, �ٽ� Ž���� �����Ѵ�.
		while (!candidate_queue.isEmpty()) {
			PuzzleKey candidate_key;
			MovingHistory candidate_history;
			candidate_queue.getCandidate(candidate_key, candidate_history);
			Puzzle candidate_puzzle;
			decodePuzzleKey(candidate_key, candidate_puzzle);

			bool is_find = false;
			for (int dir = 0; dir < 4; dir++) {
				Direction direction = static_cast<Direction>(dir);
				Puzzle next_puzzle = candidate_puzzle;
				MovingHistory next_history = candidate_history;

				next_puzzle.move(direction);
				next_history.addHistory(direction);
				PuzzleKey next_key = getPuzzleKey(next_puzzle);

				if (answer_hash_map.add(next_key, next_history)) {
					candidate_queue.addCandidate(next_key, next_history);
				}

				// direction for���� ���� ������ break; �� �� �ֵ��� is_find ���
				if (next_key == problem_key) {
					is_find = true;
					moving_history = next_history;
				}
			}
			if (is_find) break;
		}
	}

	// move by Moving History
	solveImp(puzzle, moving_history);
}