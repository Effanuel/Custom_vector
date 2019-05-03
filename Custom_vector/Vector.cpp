#include "Vector.h"

Vector::Vector(int s) : sz{ s }, elem{ new double[sz] } {}

Vector::Vector(int s, double val) : sz{ s }, elem{ new double[sz] } {
	std::fill_n(elem, s, val);
}

void Vector::setElem(int idx, double val) {
	if (idx < 0 || idx >= sz) return;
	elem[idx] = val;
}

//void Vector::resize(int count) {
//	if (count) throw std::logic_error("Cannot resize to a negative value");
//	sz = count;
//	for(int i = 0; i)
//}

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

bool Vector::operator==(const Vector& v) { // added
	if (sz == v.size()) {
		for (int i = 0; i != sz; ++i) {
			if (elem[i] != v[i]) return false;
			return true;
		}
	}
	return false;
}
bool Vector::operator!=(const Vector& v) {//added
	return !operator==(v);
}



const double& Vector::back() const {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[sz - 1];
}


double& Vector::back() {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[sz - 1];
}

const double& Vector::front() const {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[0];
}


double& Vector::front() {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[0];
}

void Vector::push_back(double v) {
	
	

}