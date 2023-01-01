#pragma once
#include "SinglyLinkedList.h"
#include "LogManager.h"
#include "TestBase.h"
#include <list>

class SinglyLinkedListTest {
private:
	template<typename T>
	static bool compareList(SinglyLinkedList<T>& user_list, std::list<T>& std_list) {
		int std_size = std_list.size();
		int user_size = user_list.size();

		if (std_size != user_size) {
			return false;
		}

		typename std::list<T>::iterator std_iter = std_list.begin();
		typename SinglyLinkedList<T>::Iterator user_iter = user_list.get_iterator();
				
		for (int i = 0; i < user_size; i++) {
			if (*std_iter != *user_iter) {
				return false;
			}
			++std_iter, ++user_iter;
		}
		return true;
	}

public:
	static void test_push_front_Int() {
		SinglyLinkedList<int> user_list;
		std::list<int> std_list;

		for (int i = 0; i < TEST_CASE_NUM; i++) {
			int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
			user_list.push_front(value);
			std_list.push_front(value);
			
			ASSERT_MSG(compareList(user_list, std_list), "Error in SinglyLinkedListTest::test_push_front_Int()\n");
		}
	}
};

