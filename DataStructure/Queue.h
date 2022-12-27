#pragma once
#include "Allocator.h"

template<typename T, typename _Allocator = DefaultAllocator<T>>
class Queue {
private:
	T* _container;
	_Allocator _allocator;
	size_t _max_size, _size;
	size_t _head_idx, _tail_idx;

public:
	T& operator[](int idx) {
		return _container[idx];
	}

	Queue(size_t max_size = 32) : 
		_max_size(max_size),
		_size(0),
		_head_idx(0),
		_tail_idx(0) {
		_container = _allocator.allocate(32);
	}
	~Queue() {
		_allocator.deallocate(_container, _max_size);
	}

	void push(T& value) {
		_container[_tail_idx] = value;
		_tail_idx++;
	}

	T& front() {
		return _container[_head_idx];
	}

	void pop() {
		_head_idx++;
	}
};


