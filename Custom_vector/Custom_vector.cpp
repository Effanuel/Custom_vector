#include "Vector.h"
#include <iostream>

int main()
{
	Vector a{ 10, 1 };
	Vector b{ 10, 2 };
	Vector c = a + b;
	for (auto i = 0; i != c.size(); ++i) std::cout << c[i] << std::endl;
}