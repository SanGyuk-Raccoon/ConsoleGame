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
};