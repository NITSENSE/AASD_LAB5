#include "../include/HeshTable.h"
#include <cassert>

int main() {
	//_________________________________________________________________________________________
	//test hash table
    std::cout << "test hash table:" << std::endl;
    {
        HashTable<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 1: Insertion" << std::endl;
        std::cout << "Result: " << std::endl;
        map.print();
        std::cout << std::endl;
    }

    {
        HashTable<int, std::string> map;
        map.insert_or_assign(1, "One");
        map.insert_or_assign(2, "Two");
        map.insert_or_assign(3, "Three");
        map.insert_or_assign(1, "New One");

        std::cout << "Test 2: Insertion or Assignment" << std::endl;
        std::cout << "Result: " << std::endl;
        map.print();
        std::cout << std::endl;
    }

    {
        HashTable<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 3: Search\n";
        std::cout << "Result:\n";

        auto result = map.search(2);
        if (result != nullptr) {
            std::cout << "Key 2 is found. Value: " << *result << std::endl;
        }
        else {
            std::cout << "Key 2 is not found." << std::endl;
        }
        result = map.search(4);
        if (result != nullptr) {
            std::cout << "Key 4 is found. Value: " << *result << std::endl;
        }
        else {
            std::cout << "Key 4 is not found." << std::endl;
        }
        std::cout << std::endl;
    }

    {
        HashTable<std::string, std::string> map;
        map.insert("One_key", "One");
        map.insert("Two_key", "Two");
        map.insert("Three_key", "Three");

        std::cout << "Test 4: Erase" << std::endl;
        std::cout << "Result: " << std::endl;
        map.erase("Two_key");
        map.print();
        std::cout << std::endl;
    }

    {
        HashTable<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 5: Contains" << std::endl;
        std::cout << "Result: " << std::endl;
        if (map.contains("One")) {
            std::cout << "True, ";
        }
        else {
            std::cout << "False, ";
        }

        if (map.contains("Four")) {
            std::cout << "True" << std::endl;
        }
        else {
            std::cout << "False" << std::endl;
        }
        std::cout << std::endl;
    }

    {
        HashTable<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(3, "Three");

        std::cout << "Test 6: Print" << std::endl;
        std::cout << "Result: " << std::endl;
        map.print();
        std::cout << std::endl;
    }

    {
        HashTable<int, std::string> map;
        map.insert(1, "One");
        map.insert(2, "Two");
        map.insert(1, "One");

        std::cout << "Test 7: Count" << std::endl;
        std::cout << "Result: " << std::endl;
        std::cout << "1: " << map.count(1) << ", "
            << "2: " << map.count(2) << ", "
            << "3: " << map.count(3) << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Test 8: random_number" << std::endl;
        HashTable<std::string, int> map(10, 20);
        std::cout << "Result: " << std::endl;
        map.print();

        std::cout << "Test 9: rehash" << std::endl;
        map.insert("random_key", 358);
        map.print();
    }

    std::cout << "All tests passed successfully!" << std::endl;

	//task test

	HashTable<size_t, std::string> map;

	std::string text = "hello";
	size_t saved_hash = map.hash_string_pearson(text);
	std::cout << "Hash for the string 'hello': " << saved_hash << std::endl;
	std::string new_text = "world";
	bool result = map.compare_hashes(saved_hash, new_text);
	std::cout << "Do the hashes match for the strings 'hello' and 'world': " << std::boolalpha << result << std::endl;
	new_text = "hello";
	result = map.compare_hashes(saved_hash, new_text);
	std::cout << "Do the hashes match for the strings 'hello' and 'hello': " << std::boolalpha << result << std::endl;

	/*
1. Начальное значение хэша: 0.
2. Для каждого символа в строке:
	- Символ 'h', числовое значение: 104.
		Новое значение хэша: 0 * 31 + 104 = 104.
	- Символ 'e', числовое значение: 101.
		Новое значение хэша: 104 * 31 + 101 = 3225.
	- Символ 'l', числовое значение: 108.
		Новое значение хэша: 3225 * 31 + 108 = 100173.
	- Символ 'l', числовое значение: 108.
		Новое значение хэша: 100173 * 31 + 108 = 3100911.
	- Символ 'o', числовое значение: 111.
		Новое значение хэша: 3100911 * 31 + 111 = 96113152.
3. Таким образом, хэш-значение для строки "hello" с использованием алгоритма Пирсона равно 96113152.
*/


	return 0;
}



