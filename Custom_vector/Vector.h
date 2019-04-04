#pragma once
#include <algorithm>

class Vector {
private:
	int sz;
	double* elem;
public:
	Vector() : sz{ 0 }, elem{ new double[sz] } {}
	Vector(int s);
	Vector(int s, double val);
	~Vector() { delete[] elem; }

	int size() const { return sz; }
	double getElem(int i) { return elem[i]; }

	void setElem(int idx, double val);
};