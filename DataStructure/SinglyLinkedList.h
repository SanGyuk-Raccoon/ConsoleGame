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
	size_t _size;
	_Alloc _allocator;

public:
	SinglyLinkedList() :
		_head(nullptr),
		_tail(nullptr),
		_size(0) {}

	~SinglyLinkedList() {
		clear();
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
	}

	size_t size() { return _size; }

	void clear() {}

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