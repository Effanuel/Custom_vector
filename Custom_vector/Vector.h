#pragma once
#include <algorithm>
#include <stdexcept>

class Vector {
private:
	int sz;
	double* elem;
public:
	Vector() : sz{ 0 }, elem{ new double[sz] } {}
	Vector(int s);
	Vector(int s, double val);
	Vector(const Vector& v) : elem{ new double[v.sz] }, sz{ v.sz }	{
		for (int i = 0; i != sz; ++i) elem[i] = v.elem[i];
	}
	Vector(std::initializer_list<double> il) 
		: sz{ static_cast<int>(il.size()) },
		elem{ new double[il.size()] }	{
		std::copy(il.begin(), il.end(), elem);
	}

	~Vector() { delete[] elem; }

	int size() const { return sz; }
	double getElem(int i) { return elem[i]; }

	void setElem(int idx, double val);

	Vector& operator=(const Vector&);

	Vector& operator=(Vector&&);

	friend Vector operator+(const Vector&, const Vector&);

	double& operator[](int i) {
		if (i < 0 || size() <= i) throw std::out_of_range{ "Vector::operator[]" };
		return elem[i];
	}
	const double& operator[](int i) const { return elem[i]; }
};