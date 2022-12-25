#pragma once
#include "Allocator.h"

template<typename T, typename _Allocator = DefaultAllocator<T>>
class Queue {
	using size_t unsigned long int;

private:
	T* container;
	_Allocator allocator;
	size_t max_size, size;
	size_t head_idx, tail_idx;

public:
	Queue(size_t max_size = 32) : 
		max_size(max_size),
		size(0),
		head_idx(0),
		tail_idx(0) {
		container = allocator.allocate(32);
	}
};


