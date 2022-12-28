#pragma once
#include "QueueTest.h"
#include "SinglyLinkedListTest.h"

class DataStructureTest {
public:
	static void testQueue() {
		QueueTest::test_Push_int();
	}

	static void testSinglyLinkedList() {
		SinglyLinkedListTest::test_push_front_Int();
	}
};
