#pragma once
#include "QueueTest.h"
#include "SinglyLinkedListTest.h"
#include "VectorTest.h"
#include "PriorityQueueTest.h"
class DataStructureTest {
public:
	static void testQueue() {
		QueueTest::test_Push_int();
	}

	static void testSinglyLinkedList() {
		SinglyLinkedListTest::push_front_int();
		SinglyLinkedListTest::push_back_int();
		SinglyLinkedListTest::pop_front_int();
		SinglyLinkedListTest::clear_int();
		SinglyLinkedListTest::push_front_ClassPointer();
	}

	static void testVector() {
		VectorTest::push_back_int();
		VectorTest::push_back_ClassPointer();
		VectorTest::pop_back_int();
	}

	static void testPQ() {
		PriorityQueueTest::test_Push_int();
	}
};
