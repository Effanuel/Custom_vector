#pragma once
#include <chrono>


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