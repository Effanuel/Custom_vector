#include <iostream>
#include "Vector.h"
#include "Timer.h"
#include <vector>
#include <string>

void Timeit(int sz, Timer start) {
	std::cout << "\tSize: "<< sz << std::endl;

	start.reset();
	std::vector<int> v1;
	for (int i = 1; i <= sz; ++i)
		v1.push_back(i);
	std::cout << "std::vector\t" << start.elapsed() << " s" << std::endl;

	start.reset();
	vector<int> v2;
	for (int i = 1; i <= sz; ++i)
		v2.push_back(1);
	std::cout << "Custom_Vector\t" << start.elapsed() << " s" << std::endl;
}

template<typename T>
int realocation(int sz, T& vec) {
	unsigned int realoc = 0;
	for (int i = 1; i <= sz; ++i) {
		vec.push_back(i);
		if (vec.capacity() == vec.size()) {
			++realoc;
		}	
	}		
	return realoc;
}


int main() {
	//unsigned int sz = 1e6;
	vector<Mock> v1;
	v1.emplace_back(4, 4.2);
	v1.emplace_back(1, 1.2);
	v1.emplace_back(22, 6.3);
	vector<int> v4 = { 1, 2, 3, 4 };
	vector<int> v3 = { 1, 2, 3, 4 };
	vector<int> v2 = std::move(v3);
	//for (auto i = 0; i != v1.size(); ++i) {
	//	std::cout << v1[i] << std::endl;
	//}
	for (auto& el : v1) {
		std::cout << el.a << std::endl;
		std::cout << el.b << std::endl;
	}

	//std::cout << "capacity()==size() for std::vector: " << realocation(sz, v1) << std::endl;
	//std::cout << "capacity()==size() for Custom_vector: " << realocation(sz, v2) << std::endl;

	//Timer start;
	//Timeit(1e5, start);
	//Timeit(1e6, start);
	//Timeit(1e7, start);
	//Timeit(1e8, start);
	//Timeit(1e9, start); //throws bad_alloc error

}