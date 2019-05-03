#include "Vector.h"
#include <iostream>
#include <vector>

int main()
{
	Vector a{ 10, 2, 4 };
	Vector b{ 10, 2, 5 };
	//std::cout << d << std::endl;
	a.push_back(4);
	for (auto i = 0; i != a.size(); ++i) std::cout << a[i] << std::endl;
}