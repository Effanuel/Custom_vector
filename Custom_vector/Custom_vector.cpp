#include "Vector.h"
#include "Timer.h"
#include <exception>


int main() {
	int sz = 1e7;
	std::vector<int> v1;
	vector<int> v2; //custom vector
	try {

		std::cout << "capacity()==size() for std::vector: " << realocation(sz, v1) << std::endl;
		std::cout << "capacity()==size() for Custom_vector: " << realocation(sz, v2) << std::endl;

		Timer start;
		Timeit(1e5, start);
		Timeit(1e6, start);
		Timeit(1e7, start);
		//Timeit(1e8, start); //throws bad_alloc error x86
		//Timeit(1e9, start); //throws bad_alloc error
	}
	catch (const std::runtime_error & e) {
		std::cout << e.what() << std::endl;
		exit(0);
	}
}
