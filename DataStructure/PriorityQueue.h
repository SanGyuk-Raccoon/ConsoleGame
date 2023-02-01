#pragma once
#include "Allocator.h"

// PQ를 만들어보자.
// Heap을 구현해본적이 없어서 해보고 싶었던 자료구조.
// ToDo : Custom Compare Function 설정할 수 있도록 하자.
template<typename T, typename _Allocator = DefaultAllocator<T>>
class PriorityQueue {
private:
	using CompareFunc = bool(*)(T&, T&);
	T* _data;
	size_t _capa, _size;
	CompareFunc _func;
	
	static bool default_compare_func(T& left, T& right) {
		return left <= right;
	}
	bool is_full();
	void resize();

public:
	PriorityQueue() {
		_func = default_compare_func;
	}

	void add(T& value);
	T& top();
	void pop();
	size_t size();
	bool is_empty();
};