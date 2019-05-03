#include <iostream>
#include "Vector.h"


int main() {
	Vector a{ 10, 2, 3 };

	for (int i = 0; i != a.size(); ++i) {
		std::cout << a[i] << std::endl;
	}
}