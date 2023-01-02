#pragma once
#include "QueueTest.h"
#include "SinglyLinkedListTest.h"

class DataStructureTest {
public:
	static void testQueue() {
		QueueTest::test_Push_int();
	}

	static void testSinglyLinkedList() {
		SinglyLinkedListTest::push_front_int();
		SinglyLinkedListTest::push_back_int();
		SinglyLinkedListTest::clear_int();
	}
};
