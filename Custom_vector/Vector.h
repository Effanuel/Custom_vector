#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <cstring>
using std::size_t;

template<class T>
class vector {
private:
	T* elem;
	size_t sz;
	size_t cap;


	void reallocate();
public:
	vector() : elem{ nullptr }, sz{}, cap{}  {}
	vector(int s);
	vector(size_t s, T val);
	vector(const vector<T>& v);
	vector(vector<T>&& v);
	vector(std::initializer_list<T> il);
	~vector();

	size_t size() const { return sz; }
	size_t capacity() const { return cap; }

	//void resize(int count);
	void setElem(int idx, T val);

	vector<T>& operator=(const vector<T>&);
	vector<T>& operator=(vector&&);
	vector<T>& operator=(std::initializer_list<T>);


	friend vector<T> operator+(const vector<T>&, const vector<T>&);

	friend vector<T> operator-(const vector<T>&, const vector<T>&);

	bool operator==(const vector<T>&);
	bool operator!=(const vector<T>&);
	bool operator>(const vector<T>&);
	bool operator<(const vector<T>&);


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
	void swap(vector<T>&);

	void push_back(const T&);
	void push_back(T&&);
	template<class ... Args> void emplace_back(Args&&... args);
	void pop_back();


	
};


template<class T>
void swap(T& a, T& b) {
	T temp{ std::move(a) };
	a = std::move(b);
	b = std::move(temp);
}

template<class T>
vector<T>::vector(const vector<T>& v) : elem{ new T[v.sz] }, sz{ v.sz }, cap{ v.cap }	{
	//for (size_t i = 0; i != sz; ++i) elem[i] = v.elem[i];
	std::cout << "vec::copy::constr" << std::endl;
	std::copy(v.elem, v.elem + v.sz, elem);
}



template<class T>
vector<T>::vector(vector<T>&& v) : elem{ nullptr }, sz{ 0 }, cap{ 0 }
{
	std::cout << "vec::move::constr" << std::endl;
	v.swap(*this);
}




template<class T>
vector<T>::vector(std::initializer_list<T> il)
	: elem{ new T[il.size()] },
	sz{ static_cast<size_t>(il.size()) }, 
	cap{ static_cast<size_t>(il.size()) }
{
	std::cout << "vec::init::list" << std::endl;
	std::copy(il.begin(), il.end(), elem);
}



template<class T>
vector<T>::~vector() { delete[] elem; }



template<class T>
vector<T>::vector(int s) : elem{ new T[s] }, sz{ s }, cap{ s } {
	for (int i = 0; i < sz; ++i)
		elem[i] = T();
}



template<class T>
vector<T>::vector(size_t s, T val) : elem{ new T[s] }, sz{ s }, cap{ s }  {
	std::fill_n(elem, s, val);
}



template<class T>
void vector<T>::setElem(int idx, T val) {
	if (idx < 0 || idx >= sz) return;
	elem[idx] = val;
}



//void vector::resize(int count) {
//	if (count) throw std::logic_error("Cannot resize to a negative value");
//	sz = count;
//	for(int i = 0; i)
//}
template<class T>
vector<T>& vector<T>::operator=(const vector<T>& v) {
	if (&v == this) return *this;
	if (cap < v.cap) {
		cap = v.cap << 1;
		reallocate();
	}
	for (size_t i = 0; i != v.sz; ++i) {
		elem[i] = v.elem[i];
	}
	sz = v.sz;
	return *this;
}
template<class T>
vector<T>& vector<T>::operator=(vector<T>&& v) {
	v.swap(*this);
	return *this;
}

template<class T> // no boundaries
T& vector<T>::operator[](size_t i) {
	return elem[i];
}
template<class T> // no boundaries
const T& vector<T>::operator[](size_t i) const	{
	return elem[i];
}


template<class T> // with boundaries
const T& vector<T>::at(size_t n) const {
	if (n < 0 || cap <= n) throw std::out_of_range{ "vector::at()" };
	return elem[n];
}

template<class T> // with boundaries
T& vector<T>::at(size_t n)	{
	if (n < 0 || cap <= n) throw std::out_of_range{ "vector::at()" };
	return elem[n];
}

template<class T>
inline const T* vector<T>::begin() const	{
	return elem;
}

template<class T>
inline const T* vector<T>::end() const
{
	return elem + sz;
}



template<class T>
vector<T> operator+(const vector<T> & a, const vector<T> & b) {
	if (a.size() != b.size())
		throw std::runtime_error("vector dydziu neatitikimas");
	auto size = a.size();
	vector<T> c(size);
	for (auto i = 0; i != a.size(); ++i)
		c[i] = a[i] + b[i];
	return c;

}
template<class T>
vector<T> operator-(const vector<T> & a, const vector<T> & b) {
	if (a.size() != b.size())
		throw std::runtime_error("vector dydziu neatitikimas");
	size_t size = a.size();
	vector<T> c( size );
	for (size_t i = 0; i != a.size(); ++i)
		c[i] = a[i] - b[i];
	return c;

}
template<class T>
bool vector<T>::operator==(const vector<T> & v) {
	if (sz == v.size()) {
		for (int i = 0; i != sz; ++i) {
			if (elem[i] != v[i]) return false;
			return true;
		}
	}
	return false;
}
template<class T>
bool vector<T>::operator!=(const vector<T> & v) {
	return !operator==(v);
}


template<class T>
inline vector<T>& vector<T>::operator=(std::initializer_list<T> il)
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
bool vector<T>::operator>(const vector<T> & v) {
	if (elem == v.elem && sz == v.size()) return false;


	auto min_siz = sz < v.size() ? sz : v.size();
	for (int i = 0; i != min_siz; ++i) {
		if (elem[i] == v.elem[i]) continue;
		return elem[i] > v.elem[i] ? true : false;

	}
	return min_siz == sz ? false : true; // if equal but one's size is greater
}

template<class T>
bool vector<T>::operator<(const vector & v) {
	if (elem == v.elem && sz == v.size()) return false;

	auto min_siz = sz < v.size() ? sz : v.size();
	for (int i = 0; i != min_siz; ++i) {
		if (elem[i] == v.elem[i]) continue;
		return elem[i] < v.elem[i] ? true : false;

	}
	return min_siz == sz ? true : false; // if equal but one's size is greater
}


template<class T>
const T& vector<T>::back() const {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[sz - 1];
}

template<class T>
T& vector<T>::back() {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[sz - 1];
}
template<class T>
const T& vector<T>::front() const {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[0];
}

template<class T>
T& vector<T>::front() {
	if (sz == 0) throw std::out_of_range("Empty vector");//added
	return elem[0];
}

template<class T>
T* vector<T>::data() noexcept
{
	return elem;
}

template<class T>
const T* vector<T>::data() const noexcept
{
	return elem;
}


template<class T>
void vector<T>::clear() {
	for (size_t i = 0; i < sz; ++i)
		elem[i].~T();
	sz = 0;
}

template<class T>
void vector<T>::reserve(size_t mem) {
	if (mem <= cap) return;
	cap = mem;
	reallocate();
}
template<class T>
inline bool vector<T>::empty() const
{
	return sz == 0;
}
template<class T>
inline void vector<T>::swap(vector<T>& other)
{
	size_t tSz, tCap;
	T* tElem;

	tElem = other.elem;
	tSz = other.sz;
	tCap = other.cap;

	other.elem = elem;
	other.sz = sz;
	other.cap = cap;

	sz = tSz;
	cap = tCap;
	elem = tElem;
}
template<class T>
void vector<T>::push_back(const T& val) {
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
inline void vector<T>::push_back(T&& val)
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
template<class ... Args>
inline void vector<T>::emplace_back(Args&& ... args)
{
	if (cap == 0) {
		reserve(1);
		reallocate();
	}
	else if (sz == cap) {
		cap <<= 1;
		reallocate();
	}
	elem[sz] = std::move(T(std::forward<Args>(args) ...));
	++sz;
}

template<class T>
inline void vector<T>::pop_back()
{
	--sz;
	elem[sz].~T();
}

template<class T>
inline void vector<T>::reallocate() //recreates vector to use new capacity
{
	T* temp = new T[cap];
	std::memcpy(temp, elem, sz * sizeof(T));
	delete[] elem;
	elem = temp;
}
