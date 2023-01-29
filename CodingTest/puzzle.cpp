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
	for (unsigned int i = 0; i < shuffle_count; i++) {
		Direction dir = static_cast<Direction>(generateRandomInt(0, 3));
		puzzle.move(dir);
	}
}

/* 위는 건들이지 말고, 아래부터 구현하면 된다. */

/*
   풀이 아이디어

   123
   456
   780

   정답 상태에서 bfs로 모든 경우의 수를 hash에 저장한다.
   이 때, (정답 -> 해당 케이스)의 이동 기록을 함께 저장한다.
   문제로 나온 케이스가 해당 hash에 당연히 있을 것이고, 이동 기록 반대로 이동시키면 된다.

   Q1)
   solve시작할 때, 굳이 모든 걸 만들어 놓을 필요없이, bfs를 하면서 문제 상황이 나올때까지만 찾는다.

   Q2)
   해당 Hash를 static으로 선언하면, Test Case가 반복됨에 따라 모든 문제에 대한 정답지를 알수있다.
   (마치 학습하는 것처럼)

   Q3)
   static과 생성자를 활용해서 solve함수가 시작되기 전, 프로그램이 시작되자마자 모든 정답지를 찾은 상태로 할수있을까?
   약간 cheating같은 느낌이긴한데 가능할지 궁금
*/
/*
   PuzzleKey

   9자리 Puzzle을 한번에 비교하기 위해 long long 의 bit를 나누어서 사용.
   0~8 이므로 최대 4bit가 필요하고, 총 9자리이기 때문에 36bit가 필요함.
   따라서, 64bit인 unsigned long long int 를 Key 자료형으로 사용함.
*/
using PuzzleKey = unsigned long long int;

/*
   MovingHistory

   이동했던 기록

   구글에서 3x3 슬라이딩 퍼즐은 최대 31번으로 풀수있다고 하는데 왜그런지 아시는분??
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
	// #1 찾아놓은 것 중에 이미 정답이 있는지 확인
	if (!answer_hash_map.find(problem_key, moving_history)) {
		// #2 위에서 찾을 수 없었다면, 다시 탐색을 시작한다.
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

				// direction for문을 전부 끝내고 break; 할 수 있도록 is_find 사용
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