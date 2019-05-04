#include <iostream>
#include "Vector.h"
#include <vector>


int main() {
	Vector<int> a{ 1, 1, 3 };
	Vector<int> b{ 1, 1, 5};
	Vector<int> c;
	b.push_back(3);
	if(b < a) std::cout << "ok" << std::endl;
	for (size_t i = 0; i != b.size(); ++i) {
		std::cout << b[i] << std::endl;
	}
}