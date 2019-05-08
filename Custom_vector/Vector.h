#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <cstring>
using std::size_t;

template<class T>
class Vector {
private:
	T* elem;
	size_t sz;
	size_t cap;



	void reallocate();
public:
	Vector() : elem{ nullptr }, sz{}, cap{}  {}
	Vector(int s);
	Vector(size_t s, T val);
	Vector(const Vector<T>& v);
	Vector(Vector<T>&& v);
	Vector(std::initializer_list<T> il);
	~Vector();

	size_t size() const { return sz; }
	size_t capacity() const { return cap; }

	//void resize(int count);
	void setElem(int idx, T val);

	Vector<T>& operator=(const Vector<T>&);
	Vector<T>& operator=(Vector&&);
	Vector<T>& operator=(std::initializer_list<T>);


	friend Vector<T> operator+(const Vector<T>&, const Vector<T>&);

	friend Vector<T> operator-(const Vector<T>&, const Vector<T>&);

	bool operator==(const Vector<T>&);
	bool operator!=(const Vector<T>&);
	bool operator>(const Vector<T>&);
	bool operator<(const Vector<T>&);


	T& operator[](size_t);
	const T& operator[](size_t) const;

	const T& at(size_t) const;
	T& at(size_t);

	const T* begin() const;
	const T* end() const;

	const T& back() const;
	T& back();
	const T& front() const;
	T& front();


	T* data() noexcept;
	const T* data() const noexcept;



	void clear();
	void reserve(size_t);
	bool empty() const;
	//bool empty() const noexcept;
	void swap(Vector<T>&);

	void push_back(const T&);
	void push_back(T&&);
	void emplace_back(const T&);
	void pop_back();


	
};


template<class T>
void swap(T& a, T& b) {
	T temp{ std::move(a) };
	a = std::move(b);
	b = std::move(temp);
}

template<class T>
Vector<T>::Vector(const Vector<T>& v) : elem{ new T[v.sz] }, sz{ v.sz }, cap{ v.cap }	{
	//for (size_t i = 0; i != sz; ++i) elem[i] = v.elem[i];
	std::cout << "vec::copy::constr" << std::endl;
	std::copy(v.elem, v.elem + v.sz, elem);
}



template<class T>
Vector<T>::Vector(Vector<T>&& v) : elem{ std::move(v.elem) }, sz{ std::move(v.sz) }, cap{ std::move(v.cap) }	{
	std::cout << "vec::move::constr" << std::endl;
	v.elem = nullptr;
	v.sz = 0;
	v.cap = 0;
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



template<class T>
Vector<T>::Vector(size_t s, T val) : elem{ new T[s] }, sz{ s }, cap{ s }  {
	std::fill_n(elem, s, val);
}



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
		cap = v.cap;
		return *this;
	}
}
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) {
	if (&v == this) return *this;
	delete[] elem;
	elem = v.elem;
	sz = v.sz;
	cap = v.cap;
	v.elem = nullptr;
	v.sz = 0;
	v.cap = 0;
	return *this;
}

template<class T> // no boundaries
T& Vector<T>::operator[](size_t i) {
	return elem[i];
}
template<class T> // no boundaries
const T& Vector<T>::operator[](size_t i) const	{
	return elem[i];
}


template<class T> // with boundaries
const T& Vector<T>::at(size_t n) const {
	if (n < 0 || cap <= n) throw std::out_of_range{ "Vector::at()" };
	return elem[n];
}

template<class T> // with boundaries
T& Vector<T>::at(size_t n)	{
	if (n < 0 || cap <= n) throw std::out_of_range{ "Vector::at()" };
	return elem[n];
}

template<class T>
inline const T* Vector<T>::begin() const	{
	return elem;
}

template<class T>
inline const T* Vector<T>::end() const
{
	return elem + sz;
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
bool Vector<T>::operator==(const Vector<T> & v) {
	if (sz == v.size()) {
		for (int i = 0; i != sz; ++i) {
			if (elem[i] != v[i]) return false;
			return true;
		}
	}
	return false;
}
template<class T>
bool Vector<T>::operator!=(const Vector<T> & v) {
	return !operator==(v);
}


template<class T>
inline Vector<T>& Vector<T>::operator=(std::initializer_list<T> il)
{
	T* temp = new T[il.size()];
	std::copy(il.begin(), il.end(), temp);
	delete[] elem;
	elem = temp;
	sz = il.size();
	cap = il.size();
	return *this;
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
T* Vector<T>::data() noexcept
{
	return elem;
}

template<class T>
const T* Vector<T>::data() const noexcept
{
	return elem;
}


template<class T>
void Vector<T>::clear() {
	delete[] elem;
	sz = 0;
	cap = 4;
	elem = new T[cap];
}
template<class T>
void Vector<T>::reserve(size_t mem) {
	if (mem <= cap) return;
	cap = mem;
	reallocate();
}
template<class T>
inline bool Vector<T>::empty() const
{
	return false;
}
template<class T>
inline void Vector<T>::swap(Vector<T>&)
{
}
template<class T>
void Vector<T>::push_back(const T& val) {
	if (cap == 0) {
		reserve(1);
		reallocate();
	} else if (sz == cap) {
		cap <<= 1;
		reallocate();
	}

	elem[sz] = val;
	++sz;
}

template<class T>
inline void Vector<T>::push_back(T&& val)
{
	if (cap == 0) {
		reserve(1);
		reallocate();
	}
	else if (sz == cap) {
		cap <<= 1;
		reallocate();
	}

	elem[sz] = std::move(val);
	++sz;
}

template<class T>
inline void Vector<T>::emplace_back(const T&)
{
}

template<class T>
inline void Vector<T>::pop_back()
{
	--sz;
	elem[sz].~T();
}

template<class T>
inline void Vector<T>::reallocate() //recreates vector to use new capacity
{
	T* temp = new T[cap];
	std::memcpy(temp, elem, sz * sizeof(T));
	delete[] elem;
	elem = temp;
}
