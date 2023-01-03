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
			ASSERT_MSG(false, "Compare Length Error in SinglyLinkedListTest. (std_size:%d, user_size:%d)\n", std_size, user_size);
		}

		typename std::list<T>::iterator std_iter = std_list.begin();
		typename SinglyLinkedList<T>::Iterator user_iter = user_list.get_iterator();
				
		for (int i = 0; i < user_size; i++) {
			if (*std_iter != *user_iter) {
				ASSERT_MSG(false, "Compare Value Error in SinglyLinkedListTest.\n");
			}
			++std_iter, ++user_iter;
		}

		if (user_size > 0) {
			ASSERT_MSG(user_list.front() == std_list.front(), "front() Error in SinglyLinkedListTest.\n");
			ASSERT_MSG(user_list.back() == std_list.back(), "back() Error in SinglyLinkedListTest.\n");
		}
		
		return true;
	}

public:
	static void push_front_int() {
		TEST_LOGGER("SinglyLinkedListTest::push_front_int()");
		SinglyLinkedList<int> user_list;
		std::list<int> std_list;
		
		for (int i = 0; i < TEST_CASE_NUM; i++) {
			int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
			user_list.push_front(value);
			std_list.push_front(value);
			
			compareList(user_list, std_list);
		}
	}

	static void push_back_int() {
		TEST_LOGGER("SinglyLinkedListTest::push_front_int()");

		SinglyLinkedList<int> user_list;
		std::list<int> std_list;

		for (int i = 0; i < TEST_CASE_NUM; i++) {
			int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
			user_list.push_back(value);
			std_list.push_back(value);

			compareList(user_list, std_list);
		}
	}

	static void clear_int() {
		TEST_LOGGER("SinglyLinkedListTest::push_front_int()");

		SinglyLinkedList<int> user_list;
		std::list<int> std_list;

		for (int i = 0; i < TEST_CASE_NUM/10; i++) {
			for (int j = 0; j < i; j++) {
				int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
				if (j & 1) {
					user_list.push_front(value);
					std_list.push_front(value);
				}
				else {
					user_list.push_back(value);
					std_list.push_back(value);
				}

				compareList(user_list, std_list);
			}
			user_list.clear();
			std_list.clear();

			compareList(user_list, std_list);
		}
	}
	
	static void push_front_ClassPointer() {
		TEST_LOGGER("SinglyLinkedListTest::push_front_ClassPointer()");

		SinglyLinkedList<TestClass*> user_list;
		std::list<TestClass*> std_list;

		for (int i = 0; i < TEST_CASE_NUM; i++) {
			int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
			TestClass* test_class = new TestClass(value);
			user_list.push_front(test_class);
			std_list.push_front(test_class);

			compareList(user_list, std_list);
		}
	}
};

