#pragma once
#include "LogManager.h"
#include "Queue.h"
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
		std::queue<int> std_queue;
		Queue<int> user_queue;

		for (int i = 0; i < 10; i++) {
			std_queue.push(i);
			user_queue.push(i);
		}

		return compareQueue(std_queue, user_queue);
	}
};