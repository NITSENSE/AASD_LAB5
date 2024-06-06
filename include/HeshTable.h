#ifndef HASHTABLE
#define HASHTABLE

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>

const double LOAD_FACTOR_THRESHOLD = 0.7; 

template<typename K, typename V>
class HashTable {
	size_t _capacity;
	size_t _size;
	std::vector<std::list<std::pair<K, V>>> _data;

	int _hash(K key) {
		std::string value;
		if constexpr (std::is_integral_v<K> || std::is_floating_point_v<K>) {
			value = std::to_string(key);
		}
		else
			value = key;
		unsigned int h = 0, a = 127;
		for (unsigned int ind = 0; ind < value.size(); ind++)
			h = (a * h + static_cast<unsigned int>(value[ind])) % _capacity;
		return (int)h;
	}

	size_t _pearson_hash(std::string value) const {
		size_t hash_value = 0;
		for (char c : value) {
			hash_value = c + (hash_value * 31);
		}
		return hash_value;
	}

	float  _load_factor_calculate() const {
		if (!_size)
			return 0;
		return (float)_size / (float)_capacity;
	}

	void _rehash() {
		size_t newCapacity = _capacity * 2;
		_capacity = newCapacity;
		std::vector<std::list<std::pair<K, V>>> newData(newCapacity);
		for (const auto& bucket : _data) {
			for (const auto& pair : bucket) {
				int newIndex = _hash(pair.first);
				newData[newIndex].push_back(pair);
			}
		}
		_data = newData;
	}

public:
	HashTable() : _capacity(10), _size(0) {
		_data.reserve(_capacity);
		for (int i = 0; i < _capacity; ++i) {
			_data.emplace_back();
		}
	}

	HashTable(size_t capacity) : _capacity(capacity), _size(0) {
		_data.reserve(capacity);
		for (int i = 0; i < capacity; ++i) {
			_data.emplace_back(); 
		}
	}

	HashTable(size_t size, size_t max_random_number) : _size(0), _capacity(size * 1.31) {
		_data.reserve(_capacity);
		for (int i = 0; i < _capacity; ++i) {
			_data.emplace_back();
		}
		for (int i = 0; i < size; i++) {
			V value = static_cast<V>(rand() % max_random_number);
			if constexpr (!std::is_integral_v<K> && !std::is_floating_point_v<K>) {
				K key = std::to_string(i); 
				insert(key, value);
			}
			else
				insert(i, value);
		}
			
	}

	HashTable(const HashTable& other) {
		_capacity = other._capacity;
		_size = other._size;
		_data = other._data;
	}

	~HashTable() {
		_data.clear();
		_size = 0;
		_capacity = 0;
	}

	HashTable& operator=(const HashTable& copy) {
		if (this != *copy) {
			_data = copy._data;
			_size = copy._size;
			_capacity = copy._capacity;
		}
		return *this;
	}

	void print() const {
		std::cout<<"_____________________________________________________________________________________________" << std::endl;
		for (auto bucket : _data) {
			if (bucket.empty())
				std::cout << "empty";
			else {
				for (auto pair : bucket) {
					std::cout << pair << " ";
					if (pair != bucket.back())
						std::cout << "-> ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << "_____________________________________________________________________________________________" << std::endl;
		std::cout << "size: " << _size << "     capacity: " << _capacity << "    load_factor: " << _load_factor_calculate() << std::endl << std::endl << std::endl;

	}

	void insert(const K& key, const V& value) {
		if (_load_factor_calculate() > LOAD_FACTOR_THRESHOLD)
			_rehash();
		if (!search(key)) {
			int index = _hash(key);
			if (_data[index].empty())
				_size++;
			_data[index].push_back(std::make_pair(key, value));
		}
	}

	void insert_or_assign(const K& key, const V& value) {
		if (_load_factor_calculate() >= LOAD_FACTOR_THRESHOLD)
			_rehash();
		int index = _hash(key);
		auto it = _data[index].begin();
		while (it != _data[index].end() && it->first != key) {
			++it;
		}
		if (it == _data[index].end()) {
			if (_data[index].empty())
				_size++;
			_data[index].push_front(std::make_pair(key, value));
		}
		else {
			it->second = value;
		}
	}

	bool contains(const V& value) {
		for (const auto& bucket : _data) {
			for (const auto& pair : bucket) {
				if (pair.second == value) {
					return true;
				}
			}
		}
		return false;
	}

	V* search(const K& key) {
		int index = _hash(key);
		for (auto it = _data[index].begin(); it != _data[index].end(); ++it) {
			if (it->first == key) {
				return &(it->second);
			}
		}
		return nullptr; 
	}

	bool erase(const K& key) {
		int index = _hash(key);
		auto it = _data[index].begin();
		while (it != _data[index].end() && it->first != key) {
			++it;
		}
		if (it != _data[index].end()) {
			_data[index].erase(it);
			if (_data[index].empty())
				_size--;
			return true;
		}
		return false;
	}
	
	int count(const K& key) {
		int index = _hash(key);
		int count = 0;
		for (auto it = _data[index].begin(); it != _data[index].end(); ++it) {
			if (it->first == key) {
				count++;
			}
		}
		return count;
	}

	size_t hash_string_pearson(const std::string& text) const {
		return _pearson_hash(text);
	}

	bool compare_hashes(size_t saved_hash, const std::string& new_text) const {
		size_t new_hash = _pearson_hash(new_text);
		return saved_hash == new_hash;
	}
};








template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& pair) {
	os << "(" << pair.first << ", " << pair.second << ")";
	return os;
}

#endif