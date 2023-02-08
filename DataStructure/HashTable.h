#pragma once
#include "Allocator.h"
#include <memory.h>

/*
ToDo : �ϴ� Bucket size�� �����ؼ� �ۼ� ��, �������� Ű�� �� �ֵ��� �غ���.
*/

constexpr unsigned int MAX_BUCKET_SIZE = 10001;

template<typename Key, typename Value>
class HashTable {
private:
	// Key type�� ���� �ٸ� hash_function �ʿ�. Ư�� ��Ʈ��.
	// template Ư��ȭ? �˾ƺ�����.
	unsigned int hash_function(Key key);
public:
	bool add(Key key, Value value);
	bool contain(Key key);
	bool find(Key key, Value& ret);
};