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

	std::vector<Pair<K, V>>* _data;
	size_t _capacity;
	static const size_t w = sizeof(K) * 8;

	size_t hash_function(const K& key) {
		return key % _capacity;
	}
public:
	HashTable() : _capacity(0) {}
	HashTable(size_t degree_of_two) : _capacity(size_t(pow(2, degree_of_two))) {
		_data = new std::vector<Pair<K, V>>[_capacity];
		_data->reserve(_capacity);
	}
	HashTable(const HashTable& other) {
		_data = other._data;
		_capacity = other._capacity;
	}
	~HashTable() {
		delete[] _data;
	}

	size_t get_capacity() const {
		return _data->capacity();
	}
	size_t get_load() const {
		return _data->size();
	}

};

#endif // !LAB_5_INCLUDE_HASHTABLE_H