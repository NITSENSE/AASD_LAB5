#include "../include/HeshTable.h"

int main() {
	HashTable<std::string, int> a(10, 15);
	a.print();
	a.insert("jkasdf", 6);
	a.print();
	a.insert_or_assign("jkasdf", 12);
	a.insert_or_assign("jityf", 13);
	a.insert_or_assign("jkeyref", 14);
	a.insert_or_assign("jkwewwwwdf", 15);
	a.insert_or_assign("jkaertyuf", 16);
	a.insert_or_assign("jkfghjsdf", 17);
	a.print();
	a.erase("jkasdf");
	a.erase("jityf");
	a.erase("jkeyref");
	a.erase("jkwewwwwdf");
	a.erase("jkaertyuf");
	a.erase("jkfghjsdf");
	a.print();
	std::cout << a.contains(12);

	return 0;
}



