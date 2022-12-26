#pragma once
#include "QueueTest.h"

class DataStructureTest {
public:
	static void testQueue() {
		ASSERT_MSG(QueueTest::test_Push_int(), "ERROR in Queue Test(push(int))!\n");
	}
};
