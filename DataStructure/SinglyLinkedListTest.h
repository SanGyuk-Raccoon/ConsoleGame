#pragma once
#include "SinglyLinkedList.h"
#include "LogManager.h"
#include "TestBase.h"

class SinglyLinkedListTest {
public:
	static void test_push_front_Int() {
		SinglyLinkedList<int> user_list;

		for (int i = 0; i < TEST_CASE_NUM; i++) {
			int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
			user_list.push_front(value);
		}
	}
};

