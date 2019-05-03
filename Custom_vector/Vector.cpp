#include "Vector.h"

template<class T>
void swap(T& a, T& b) {
	T temp{ std::move(a) };
	a = std::move(b);
	b = std::move(temp);
}

Vector::Vector(const Vector& v) : elem{ new double[v.sz] }, sz{ v.sz }	{
	for (int i = 0; i != sz; ++i) elem[i] = v.elem[i];
}

Vector::Vector(Vector&& v) : sz{ v.sz }, elem{ v.elem }	{
	v.elem = nullptr;
	v.sz = 0;
}

Vector::Vector(std::initializer_list<double> il)
	: sz{ static_cast<int>(il.size()) },
	elem{ new double[il.size()] }	{
	std::copy(il.begin(), il.end(), elem);
}

Vector::~Vector() { delete[] elem; }


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

Vector operator-(const Vector& a, const Vector& b) {
	if (a.size() != b.size())
		throw std::runtime_error("Vector dydziu neatitikimas");
	auto size = a.size();
	Vector c(size);
	for (auto i = 0; i != a.size(); ++i)
		c[i] = a[i] - b[i];
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


bool Vector::operator>(const Vector& v) {
	if (elem == v.elem && sz == v.size()) return false;
		

	auto min_siz = sz < v.size() ? sz : v.size();
	for (int i = 0; i != min_siz; ++i) {
		if (elem[i] == v.elem[i]) continue;
		return elem[i] > v.elem[i] ? true : false;
			
	} 
	return min_siz == sz ? false : true; // if equal but one's size is greater
}

bool Vector::operator<(const Vector& v) {
	if (elem == v.elem && sz == v.size()) return false;

	auto min_siz = sz < v.size() ? sz : v.size();
	for (int i = 0; i != min_siz; ++i) {
		if (elem[i] == v.elem[i]) continue;
		return elem[i] < v.elem[i] ? true : false;

	}
	return min_siz == sz ? true : false; // if equal but one's size is greater
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

//void Vector::push_back(double v) {
//	
//	
//
//}