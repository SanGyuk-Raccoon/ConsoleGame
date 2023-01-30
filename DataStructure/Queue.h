#pragma once
#include "Allocator.h"
#include "Vector.h"

template<typename T, typename _Allocator = DefaultAllocator<T>, typename _Container = Vector<T, _Allocator>>
class Queue {
private:
	_Container _container;

public:
	T& operator[](int idx) {
		return _container[idx];
	}

	void push(T& value) {
		_container.push_back(value);
	}

	T& front() {
		return _container.front();
	}

	void pop() {
		_container.pop_front();
	}
};


