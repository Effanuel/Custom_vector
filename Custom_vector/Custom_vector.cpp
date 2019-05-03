#include <iostream>
#include "Vector.h"
#include <vector>


int main() {
	Vector a{ 1, 1, 3 };
	Vector b{ 1, 1, -10};
	Vector c = a - b;
	if(b < a) std::cout << "ok" << std::endl;
	for (int i = 0; i != c.size(); ++i) {
		std::cout << c[i] << std::endl;
	}
}