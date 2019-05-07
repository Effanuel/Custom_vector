#include <iostream>
#include "Vector.h"
#include "Timer.h"
#include <vector>


void Timeit(unsigned int sz, Timer start) {
	std::cout << "\tSize: "<< sz << std::endl;

	start.reset();
	std::vector<int> v1;
	for (int i = 1; i <= sz; ++i)
		v1.push_back(i);
	std::cout << "std::vector\t" << start.elapsed() << " s" << std::endl;

	start.reset();
	Vector<int> v2;
	for (int i = 1; i <= sz; ++i)
		v2.push_back(1);
	std::cout << "Custom_Vector\t" << start.elapsed() << " s" << std::endl;
}


int main() {
	Timer start;
	Timeit(1e5, start);
	Timeit(1e6, start);
	Timeit(1e7, start);
	Timeit(1e8, start);
	//Timeit(1e9, start); //throws bad_alloc error

}