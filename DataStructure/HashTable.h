#pragma once
#include "Allocator.h"
#include <memory.h>

/*
ToDo : 일단 Bucket size를 고정해서 작성 후, 동적으로 키울 수 있도록 해보자.
*/

constexpr unsigned int MAX_BUCKET_SIZE = 10001;

template<typename Key, typename Value>
class HashTable {
private:
	// Key type에 따라서 다른 hash_function 필요. 특히 스트링.
	// template 특수화? 알아봐야함.
	unsigned int hash_function(Key key);
public:
	bool add(Key key, Value value);
	bool contain(Key key);
	bool find(Key key, Value& ret);
};