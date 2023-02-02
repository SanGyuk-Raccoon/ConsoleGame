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
	_Allocator _allocator;

	static bool default_compare_func(T& left, T& right) {
		return left < right;
	}
	bool is_full() {
		return _capa == _size;
	}
	void resize() {
		// 배열이 가득 차면 늘려주자.
	}
	void swap(T& left, T& right) {
		T tmp = left;
		left = right;
		right = tmp;
	}
	void heapify(size_t index) {
		// heapify 이해 필요
	}

public:
	PriorityQueue(CompareFunc func = default_compare_func): _capa(1<<5), _size(0), _func(func) {
		_data = _allocator.allocate(_capa);
	}

	void enqueue(T& value) {
		if (is_full()) {
			resize();
		}

		size_t i = ++_size;
		_data[i] = value;

		if (i == 1) return;
		while (_func(_data[i / 2], _data[i])) {
			swap(_data[i / 2], _data[i]));
			i /= 2;
		}
	}
	T& peek() {
		ASSERT_MSG(is_empty() == false, "PriorityQueue::peek() : Priority Queue is Empty!");
		return _data[1];
	}
	// heapify 구현 후, 구현하기.
	T& dequeue();
	size_t size() { return _size; }
	bool is_empty() {
		return _size == 0;
	}
};