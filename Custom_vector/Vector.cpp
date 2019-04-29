#include "Vector.h"

Vector::Vector(int s) : sz{ s }, elem{ new double[sz] } {}

Vector::Vector(int s, double val) : sz{ s }, elem{ new double[sz] } {
	std::fill_n(elem, s, val);
}

void Vector::setElem(int idx, double val) {
	if (idx < 0 || idx >= sz) return;
	elem[idx] = val;
}

Vector& Vector::operator=(const Vector& v) {

	if (&v == this) return *this;

	double* p = new double[v.sz];
	for (int i = 0; i != v.sz; ++i) {
		p[i] = v.elem[i];
		delete[] elem;
		elem = p;
		sz = v.sz;
		return *this;
	}
}

Vector& Vector::operator=(Vector&& v) {
	if (&v == this) return *this;
	delete[] elem;
	elem = v.elem;
	sz = v.sz;
	v.elem = nullptr;
	v.sz = 0;
	return *this;
}

Vector operator+(const Vector& a, const Vector& b) {
	if (a.size() != b.size())
		throw std::runtime_error("Vector dydziu neatitikimas");
	auto size = a.size();
	Vector c(size);
	for (auto i = 0; i != a.size(); ++i)
		c[i] = a[i] + b[i];
	return c;

}