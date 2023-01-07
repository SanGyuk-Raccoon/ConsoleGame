#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "LogManager.h"

#define _DebugLog (0)
#if _DebugLog
#define Print_Alloc_Log(p, size) printf("Alloc Log : \n\tAddr : %p\n\tSize : %d\n", p, size)
#define Print_Dealloc_Log(p, size) printf("Dealloc Log : \n\tAddr : %p\n\tSize : %d\n", p, size)
#else
#define Print_Alloc_Log(p, size)
#define Print_Dealloc_Log(p, size)
#endif


template<typename T>
class DefaultAllocator {
	size_t _allocate_count;

public:
	DefaultAllocator() : _allocate_count(0) {}
	~DefaultAllocator() {
		ASSERT_MSG(_allocate_count == 0, "");		
	}
	T* allocate(size_t size) {
		T* p = new T[size];
		Print_Alloc_Log(p, size);
		_allocate_count += size;
		return p;
	}

	void deallocate(T* p, size_t size) {
		Print_Dealloc_Log(p, size);
		_allocate_count -= size;
		delete[] p;
	}
};