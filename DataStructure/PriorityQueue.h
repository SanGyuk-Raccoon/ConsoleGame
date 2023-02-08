#pragma once
#include "Allocator.h"
#include <memory.h>

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
		T* tmp = _allocator.allocate(_capa << 1);
		memcpy(tmp, _data, _capa);
		_allocator.deallocate(_data, _capa);
		_capa <<= 1;
		_data = tmp;
	}
	void swap(T& left, T& right) {
		T tmp = left;
		left = right;
		right = tmp;
	}
	void heapify(size_t index) {
		size_t cur_index(index);
		size_t left_child_index(0), right_child_index(0);
		
		while (left_child_index = 2 * cur_index + 1 < _size) {
			size_t changed_child_index = left_child_index;
			if (right_child_index < _size && _func(_data[left_child_index], _data[right_child_index])) {
				changed_child_index = right_child_index;
			}

			if (_func(_data[cur_index], _data[changed_child_index])) {
				swap(_data[cur_index], _data[changed_child_index]);
				cur_index = changed_child_index;
			}
			else {
				break;
			}
		}
	}

public:
	PriorityQueue(CompareFunc func = default_compare_func): _capa(1<<5), _size(0), _func(func) {
		_data = _allocator.allocate(_capa);
	}
	~PriorityQueue() {
		_allocator.deallocate(_data, _capa);
	}
	void enqueue(T& value) {
		if (is_full()) {
			resize();
		}
		size_t cur_index = _size++;
		size_t parent_index = 0;
		_data[cur_index] = value;

		while (cur_index > 0 && _func(_data[parent_index = (cur_index - 1) / 2], _data[cur_index])) {
			swap(_data[parent_index], _data[cur_index]);
			cur_index = parent_index;
		}
	}
	T& peek() {
		ASSERT_MSG(is_empty() == false, "PriorityQueue::peek() : Priority Queue is Empty!");
		return _data[0];
	}
	// heapify 구현 후, 구현하기.
	T& dequeue() {
		_size--;
		swap(_data[0], _data[_size]);
		heapify(0);
		return _data[_size];
	}
	size_t size() { return _size; }
	bool is_empty() {
		return _size == 0;
	}
};