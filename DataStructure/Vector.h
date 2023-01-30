#pragma once
#include "Allocator.h"
#include <memory.h>

template<typename T, typename _Alloc = DefaultAllocator<T>>
class Vector {
private:
	_Alloc _allocator;
	T* _data;
	size_t _capa, _size;
	void resize() {
		T* tmp = _allocator.allocate(_capa << 1);
		memcpy(tmp, _data, sizeof(T)*_capa);
		_allocator.deallocate(_data, _capa);
		_data = tmp;
		_capa <<= 1;
	}

public:
	Vector() : _capa(1<<4), _size(0) {
		_data = _allocator.allocate(_capa);
	}
	~Vector() {
		_allocator.deallocate(_data, _capa);
	}

	T& operator[](int index) {
		ASSERT_MSG(0 <= index && index < _size, "Panic in Vector Operator[] : Invalid Index(_size:%d, index:%d)", _size, index);
		return _data[index];
	}
	void push_back(T& value) {
		if (is_full()) {
			resize();
		}
		_data[_size] = value;
		_size++;
	}
	T& front() {
		ASSERT_MSG(_size > 0, "Panic in front() : Vector is Empty");
		return _data[0];
	}
	void pop_front() {
		// 일단 무식하게 복사하는 걸로 구현해놓음. 이후에 수정 필요.
		T* tmp = _allocator.allocate(_capa);
		_size--;
		memcpy(tmp, _data + 1, sizeof(T) * _size);
		_allocator.deallocate(_data, _capa);
		_data = tmp;
	}

	T& back() {
		ASSERT_MSG(_size > 0, "Panic in back() : Vector is Empty");
		return _data[_size - 1];
	}
	void pop_back() {
		_size--;
	}
	bool is_empty() { return _size == 0; }
	bool is_full() { return _size == _capa; }
	void clear() {
		_size = 0;
	}
	size_t size() { return _size; }
};