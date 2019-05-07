#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>

using std::size_t;

template<class T> class Vector {
private:
	T* elem;
	size_t sz;
	size_t cap;

public:
	Vector() : elem{ nullptr }, sz{}, cap{}  {}
	Vector(int s);
	//Vector(int s, T val);
	Vector(const Vector& v);
	Vector(Vector&& v);
	Vector(std::initializer_list<T> il);
	~Vector();

	size_t size() const { return sz; }
	size_t capacity() const { return cap; }

	//void resize(int count);
	T getElem(int i) const { return elem[i]; }
	void setElem(int idx, T val);

	Vector<T>& operator=(const Vector<T>&);
	Vector<T>& operator=(Vector&&);

	friend Vector<T> operator+(const Vector<T>&, const Vector<T>&);
	friend Vector<T> operator-(const Vector<T>&, const Vector<T>&);

	bool operator==(const Vector<T>&);
	bool operator!=(const Vector<T>&);
	bool operator>(const Vector<T>&);
	bool operator<(const Vector<T>&);

	T& operator[](size_t i) {
		if (i < 0 || capacity() <= i) throw std::out_of_range{ "Vector::operator[]" };
		return elem[i];
	}
	const T& operator[](size_t i) const { return elem[i]; }

	const T& back() const;
	T& back();
	const T& front() const;
	T& front();

	void clear();
	void reserve(int);

	void push_back(const T&);
};


template<class T>
void swap(T& a, T& b) {
	T temp{ std::move(a) };
	a = std::move(b);
	b = std::move(temp);
}

template<class T>
Vector<T>::Vector(const Vector& v) : elem{ new T[v.sz] }, sz{ v.sz }, cap{ v.cap }	{
	for (size_t i = 0; i != sz; ++i) elem[i] = v.elem[i];
}



template<class T>
Vector<T>::Vector(Vector&& v) : elem{ v.elem }, sz{ v.sz }, cap{ v.cap }	{
	v.elem = nullptr;
	v.sz = 0;
	v.cap = 8;
}




template<class T>
Vector<T>::Vector(std::initializer_list<T> il)
	: elem{ new T[il.size()] },
	sz{ static_cast<size_t>(il.size()) }, 
	cap{ static_cast<size_t>(il.size()) }
		{
			std::copy(il.begin(), il.end(), elem);
		}



template<class T>
Vector<T>::~Vector() { delete[] elem; }



template<class T>
Vector<T>::Vector(int s) : elem{ new T[s] }, sz{ s }, cap{ s } {
	for (int i = 0; i < sz; ++i)
		elem[i] = T();
}



//template<class T>
//Vector<T>::Vector(int s, T val) : elem{ new T[s] }, sz{ s }, cap{ s }  {
//	std::fill_n(elem, s, val);
//}



template<class T>
void Vector<T>::setElem(int idx, T val) {
	if (idx < 0 || idx >= sz) return;
	elem[idx] = val;
}



//void Vector::resize(int count) {
//	if (count) throw std::logic_error("Cannot resize to a negative value");
//	sz = count;
//	for(int i = 0; i)
//}
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T> & v) {
	if (&v == this) return *this;
	T* p = new T[v.sz];
	for (int i = 0; i != v.sz; ++i) {
		p[i] = v.elem[i];
		delete[] elem;
		elem = p;
		sz = v.sz;
		return *this;
	}
}
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) {
	if (&v == this) return *this;
	delete[] elem;
	elem = v.elem;
	sz = v.sz;
	v.elem = nullptr;
	v.sz = 0;
	return *this;
}
template<class T>
Vector<T> operator+(const Vector<T> & a, const Vector<T> & b) {
	if (a.size() != b.size())
		throw std::runtime_error("Vector dydziu neatitikimas");
	auto size = a.size();
	Vector<T> c(size);
	for (auto i = 0; i != a.size(); ++i)
		c[i] = a[i] + b[i];
	return c;

}
template<class T>
Vector<T> operator-(const Vector<T> & a, const Vector<T> & b) {
	if (a.size() != b.size())
		throw std::runtime_error("Vector dydziu neatitikimas");
	size_t size = a.size();
	Vector<T> c( size );
	for (size_t i = 0; i != a.size(); ++i)
		c[i] = a[i] - b[i];
	return c;

}
template<class T>
bool Vector<T>::operator==(const Vector<T> & v) { // added
	if (sz == v.size()) {
		for (int i = 0; i != sz; ++i) {
			if (elem[i] != v[i]) return false;
			return true;
		}
	}
	return false;
}
template<class T>
bool Vector<T>::operator!=(const Vector<T> & v) {//added
	return !operator==(v);
}

template<class T>
bool Vector<T>::operator>(const Vector<T> & v) {
	if (elem == v.elem && sz == v.size()) return false;


	auto min_siz = sz < v.size() ? sz : v.size();
	for (int i = 0; i != min_siz; ++i) {
		if (elem[i] == v.elem[i]) continue;
		return elem[i] > v.elem[i] ? true : false;

	}
	return min_siz == sz ? false : true; // if equal but one's size is greater
}

template<class T>
bool Vector<T>::operator<(const Vector & v) {
	if (elem == v.elem && sz == v.size()) return false;

	auto min_siz = sz < v.size() ? sz : v.size();
	for (int i = 0; i != min_siz; ++i) {
		if (elem[i] == v.elem[i]) continue;
		return elem[i] < v.elem[i] ? true : false;

	}
	return min_siz == sz ? true : false; // if equal but one's size is greater
}


template<class T>
const T& Vector<T>::back() const {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[sz - 1];
}

template<class T>
T& Vector<T>::back() {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[sz - 1];
}
template<class T>
const T& Vector<T>::front() const {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[0];
}

template<class T>
T& Vector<T>::front() {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[0];
}

template<class T>
void Vector<T>::clear() {
	delete[] elem;
	sz = 0;
	cap = 4;
	elem = new T[cap];
}
template<class T>
void Vector<T>::reserve(int mem) {
	if (mem <= cap) return;

	T* temp = new T[mem];

	for (int i = 0; i < sz; ++i) {
		temp[i] = elem[i];
	}
	delete[] elem;
	cap = mem;
	elem = temp;
	
}
template<class T>
void Vector<T>::push_back(const T& val) {
	if (cap == 0)
		reserve(8);
	else if (sz == cap)
		reserve(2 * cap);

	elem[sz] = val;
	++sz;
}
