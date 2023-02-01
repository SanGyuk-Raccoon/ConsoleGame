#pragma once
#include "Allocator.h"

// PQ�� ������.
// Heap�� �����غ����� ��� �غ��� �;��� �ڷᱸ��.
// ToDo : Custom Compare Function ������ �� �ֵ��� ����.
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