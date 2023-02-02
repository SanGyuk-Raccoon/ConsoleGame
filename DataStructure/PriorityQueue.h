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
	_Allocator _allocator;

	static bool default_compare_func(T& left, T& right) {
		return left < right;
	}
	bool is_full() {
		return _capa == _size;
	}
	void resize() {
		// �迭�� ���� ���� �÷�����.
	}
	void swap(T& left, T& right) {
		T tmp = left;
		left = right;
		right = tmp;
	}
	void heapify(size_t index) {
		// heapify ���� �ʿ�
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
	// heapify ���� ��, �����ϱ�.
	T& dequeue();
	size_t size() { return _size; }
	bool is_empty() {
		return _size == 0;
	}
};