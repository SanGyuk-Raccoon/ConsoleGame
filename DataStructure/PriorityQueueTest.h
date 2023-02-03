#pragma once
#include "PriorityQueue.h"
#include "LogManager.h"
#include "TestBase.h"
#include <queue>

class PriorityQueueTest {
private:
	template<typename T>
	static bool comparePQ(std::priority_queue<T>& std_pq, PriorityQueue<T>& user_pq) {
		int size = std_pq.size();
		for (int i = 0; i < size; i++) {
			if (user_pq.peek() != std_pq.top()) return false;
			user_pq.dequeue();
			std_pq.pop();
		}
		return true;
	}

public:
	static bool test_Push_int() {
		{
			std::priority_queue<int> std_queue;
			PriorityQueue<int> user_queue;

			for (int i = 0; i < TEST_CASE_NUM; i++) {
				int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
				std_queue.push(value);
				user_queue.enqueue(value);
			}
		}
		printf("PriorityQueue Test - Push(int) : SUCCESS\n");
		return true;
	}
};