#pragma once
#include <iostream>
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
	Vector(const Vector& v);
	Vector(Vector&& v);
	Vector(std::initializer_list<double> il);
	~Vector();

	int size() const { return sz; }
	//void resize(int count);
	double getElem(int i) const { return elem[i]; }
	void setElem(int idx, double val);

	Vector& operator=(const Vector&);
	Vector& operator=(Vector&&);

	friend Vector operator+(const Vector&, const Vector&);
	friend Vector operator-(const Vector&, const Vector&);

	bool operator==(const Vector&);
	bool operator!=(const Vector&);
	bool operator>(const Vector&);
	bool operator<(const Vector&);

	double& operator[](int i) {
		if (i < 0 || size() <= i) throw std::out_of_range{ "Vector::operator[]" };
		return elem[i];
	}
	const double& operator[](int i) const { return elem[i]; }

	const double& back() const;
	double& back();
	const double& front() const;
	double& front();
};