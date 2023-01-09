#pragma once
#include "Vector.h"
#include "LogManager.h"
#include "TestBase.h"
#include <vector>

class VectorTest {
private:
	template<typename T>
	static void compareVector(Vector<T>& user_vector, std::vector<T>& std_vector) {
		// compare Size
		{
			size_t user_size = user_vector.size();
			size_t std_size = std_vector.size();
			ASSERT_MSG(std_size == user_size, "Compare Length Error in SinglyLinkedListTest. (std_size:%d, user_size:%d)\n", std_size, user_size);
		}

		// compare Value
		{
			size_t size = user_vector.size();
			for (size_t i = 0; i < size; i++) {
				ASSERT_MSG(std_vector[i] == user_vector[i], "Compare Value Error in VectorTest.");
			}
		}
		
		// compare front/back
		if (user_vector.is_empty() == false) {
			ASSERT_MSG(user_vector.front() == std_vector.front(), "front() Error in VectorTest.");
			ASSERT_MSG(user_vector.back() == std_vector.back(), "back() Error in VectorTest.");
		}
	}
public:
	static void push_back_int() {
		TEST_LOGGER("VectorTest::push_front_int()");

		Vector<int> user_vector;
		std::vector<int> std_vector;

		for (int i = 0; i < TEST_CASE_NUM; i++) {
			int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
			user_vector.push_back(value);
			std_vector.push_back(value);

			compareVector(user_vector, std_vector);
		}
	}
	static void push_back_ClassPointer() {
		TEST_LOGGER("VectorTest::push_back_ClassPointer()");

		Vector<TestClass*> user_vector;
		std::vector<TestClass*> std_vector;

		for (int i = 0; i < TEST_CASE_NUM; i++) {
			int value = RandomGenerator::generateRandomInt(MIN_INT32, MAX_INT32);
			TestClass* new_class = new TestClass(value);
			user_vector.push_back(new_class);
			std_vector.push_back(new_class);

			compareVector(user_vector, std_vector);
		}

		for (int i = 0; i < TEST_CASE_NUM; i++) {
			delete user_vector[i];
		}
	}
};