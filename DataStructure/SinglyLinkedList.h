#pragma once
#include "Allocator.h"
#include <list>

template<typename T> 
struct SinglyLinkedListNode {
	T value;
	SinglyLinkedListNode* next;
	SinglyLinkedListNode() :
		value(), next(nullptr) {}
};


template<typename T, typename _Alloc = DefaultAllocator<SinglyLinkedListNode<T>>>
class SinglyLinkedList {
	using Node = SinglyLinkedListNode<T>;
private:
	Node* _head, *_tail;
	_Alloc _allocator;
	size_t _size;

public:
	SinglyLinkedList() :
		_head(nullptr),
		_tail(nullptr),
		_size(0) {}

	~SinglyLinkedList() {
		clear();
	}

	T& front() {
		ASSERT_MSG(_head != nullptr, "List is Empty\n");
		return _head->value;
	}

	void push_front(T& value) {
		Node* new_node = _allocator.allocate(1);
		new_node->value = value;

		if (_head == nullptr) {
			_head = _tail = new_node;
		}
		else {
			new_node->next = _head;
			_head = new_node;
		}
		_size++;
	}

	void pop_front() {
		ASSERT_MSG(_head != nullptr, "List is Empty.");
		Node* tmp = _head;
		_head = _head->next;
		_allocator.deallocate(tmp, 1);
		_size--;
	}

	T& back() {
		ASSERT_MSG(_tail != nullptr, "List is Empty.");
		return _tail->value;
	}

	void push_back(T& value) {	
		Node* new_node = _allocator.allocate(1);
		new_node->value = value;

		if (_tail == nullptr) {
			_head = _tail = new_node;
		}
		else {
			_tail->next = new_node;
			_tail = new_node;
		}
		_size++;
	}

	size_t size() { return _size; }

	bool is_empty() { return _size == 0; }

	void clear() {
		while (_head != nullptr) {
			Node* tmp = _head;
			_head = _head->next;
			_allocator.deallocate(tmp, 1);
		}
		_head = _tail = nullptr;
		_size = 0;
	}

	class Iterator {
	private:
		Node* _head;

	public:
		Iterator(Node* head = nullptr) : _head(head) {}
		Iterator& operator++() {
			if (_head != nullptr) {
				_head = _head->next;
			}
			return *this;
		}
		T& operator*() {
			return _head->value;
		}
	};

	typename SinglyLinkedList<T>::Iterator get_iterator() {
		return Iterator(_head);
	}
};