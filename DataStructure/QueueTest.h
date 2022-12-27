#pragma once
#include "Queue.h"
#include "LogManager.h"
#include "TestBase.h"
#include <queue>

class QueueTest {
private:
	template<typename T>
	static bool compareQueue(std::queue<T>& std_queue, Queue<T>& user_queue) {
		int size = std_queue.size();
		for (int i = 0; i < size; i++) {
			if (user_queue.front() != std_queue.front()) return false;
			user_queue.pop();
			std_queue.pop();
		}
		
		return true;
	}

public:
	static bool test_Push_int() {
		{
			std::queue<int> std_queue;
			Queue<int> user_queue;

			
			for (int i = 0; i < TEST_CASE_NUM; i++) {
				int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
				std_queue.push(value);
				user_queue.push(value);
			}
		}

		printf("Queue Test - Push(int) : SUCCESS\n");
		return true;
	}
};