#pragma once
#include <stdlib.h>
#include <stdio.h>


#define _DebugLog (1);
#if _DebugLog
#define Print_Alloc_Log(p, size) printf("Alloc Log : \n\tAddr : %p\n\tSize : %d\n", p, size)
#define Print_Dealloc_Log(p, size) printf("Dealloc Log : \n\tAddr : %p\n\tSize : %d\n", p, size)
#else
#define Print_Alloc_Log(p, size)
#define Print_Dealloc_Log(p, size)
#endif


template<typename T>
class DefaultAllocator {
public:
	T* allocate(size_t size) {
		T* p = new T[size];
		Print_Alloc_Log(p, size);
		return p;
	}

	void deallocate(T* p, size_t size) {
		Print_Dealloc_Log(p, size);
		delete[] p;
	}
};