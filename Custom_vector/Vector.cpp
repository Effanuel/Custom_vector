#include "Vector.h"

Vector::Vector(int s) : sz{ s }, elem{ new double[sz] } {}

Vector::Vector(int s, double val) : sz{ s }, elem{ new double[sz] } {
	std::fill_n(elem, s, val);
}

void Vector::setElem(int idx, double val) {
	if (idx < 0 || idx >= sz) return;
	elem[idx] = val;
}