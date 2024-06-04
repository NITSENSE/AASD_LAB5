#ifndef HASHTABLE
#define HASHTABLE

#include <iostream>
#include <vector>
#include <cmath>


template<typename K, typename V>
struct Pair {
	K key;
	V value;
	Pair(const K& key, const V& value) : key(key), value(value) {}
};

template<typename K, typename V>
class HashTable {

	Pair<K, V>* _data;
	static const size_t _default_size = 100;
	size_t hash_function(const K& key) {
		return key % _capacity;
	}
public:
	HashTable() : _capacity(0) {}
	HashTable(size_t size = _default_size) : _size(size), _data(new Pair<K, V>[size]) {};
	HashTable(size_t size, size_t max_random_number) : _size(size), _data(new Pair<K, V>[size]) {
		for (size_t i = 0; i < _size; i++) {
			K key = static_cast<K>(i);
			V value = static_cast<V>(rand() % max_random_number);
			insert(key, value);
		}
			
	}
	HashTable(const HashTable& other) : _size(size), _data(new Pair<K, V>[size]) {
		for (int i = 0; i < _size; i++) 
			_data[i] = other._data[i];
	}
	~HashTable() {
		delete[] _data;
	}
	
};

#endif 