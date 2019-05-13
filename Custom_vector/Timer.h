#pragma once
#include <chrono>
#include <vector>
#include <iostream>
#include <string>

class Timer {
private:
	///Auksto tikslumo laikrodi
	using hrClock = std::chrono::high_resolution_clock;
	///Double trukmes skaiciavimas
	using durationDouble = std::chrono::duration<long double>;
	std::chrono::time_point<hrClock> start;
public:
	///Sukuria Timer() objekta, pradeda skaiciuoti laika
	Timer() : start{ hrClock::now() } {}
	///Pradeda skaiciuoti laika is pradziu
	void reset() {
		start = hrClock::now();
	}
	///Grazina laika nuo Timer() sukurimo/reset() iki sios funkcijos call
	long double elapsed() const {
		return durationDouble(hrClock::now() - start).count();
	}
};


void Timeit(int sz, Timer start) {
	std::cout << "\tSize: " << sz << std::endl;

	start.reset();
	std::vector<int> v1;
	for (int i = 1; i <= sz; ++i)
		v1.push_back(i);
	std::cout << "std::vector\t" << start.elapsed() << " s" << std::endl;
	v1.clear();

	start.reset();
	vector<int> v2;
	for (int i = 1; i <= sz; ++i)
		v2.push_back(i);
	std::cout << "Custom_Vector\t" << start.elapsed() << " s" << std::endl;
	v2.clear();
}

template<typename T>
int realocation(int sz, T& vec) {
	int realoc = 0;
	for (int i = 1; i <= sz; ++i) {
		vec.push_back(i);
		if (vec.capacity() == vec.size()) {
			++realoc;
		}
	}
	//vec.clear();
	return realoc;
}
