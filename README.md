# Custom_vector






|   | 100,000  | 1,000,000   | 10,000,000   |  100,000,000  |
|---|---|---|---|---|
|  std::vector | 0.0012542  | 0.0073552  |  0.0889958   |  0.911318 |
| Custom_vector  |  0.0005783 |   0.0052092 | 0.0729189  | 0.540884  |

---

```c++
#include <gtest/gtest.h>
#include "../Custom_vector/Vector.h"
#include <vector>
typedef vector<int> vint;
typedef vector<Mock> vMock;
...
```
## Member functions:
### 1. reserve(std::size_t mem)
```C++
...
template<class T>
void vector<T>::reserve(size_t mem) {
	if (mem <= cap) return;
	cap = mem;
	reallocate();
}
...
TEST(Capacity, Reserve)
{
	vint vec;
	vec.reserve(100);

	EXPECT_EQ(100, vec.capacity());
}
```
### 2. clear()
```C++
...
template<class T>
void vector<T>::clear() {
	for (size_t i = 0; i < sz; ++i)
		elem[i].~T();
	sz = 0;
}
...
TEST(Modifier, Clear)
{
	vint vec({ 1, 2, 3, 4 });
	vec.clear();

	EXPECT_EQ(0, vec.size());
}
```

### 3. emplace_back()
```C++
...
template<class T>
template<class ... Args>
inline void vector<T>::emplace_back(Args&&... args)
{
	if (cap == 0) {
		reserve(1);
		reallocate();
	}
	else if (sz == cap) {
		cap <<= 1;
		reallocate();
	}
	elem[sz] = std::move(T(std::forward<Args>(args)...));
	++sz;
}
...
TEST(Modifier, EmplaceBack)
{
	vMock vec;
	vec.emplace_back(9, 3.2);
	vec.emplace_back(22, 33);

	EXPECT_EQ(9, vec[0].a);
	EXPECT_EQ(3.2, vec[0].b);
	EXPECT_EQ(22, vec[1].a);
	EXPECT_EQ(33, vec[1].b);
}
```

### 4. push_back()
```C++
...
template<class T>
void vector<T>::push_back(const T& val) {
	if (cap == 0) {
		reserve(1);
		_reallocate();
	} else if (sz == cap) {
		cap <<= 1;
		_reallocate();
	}

	elem[sz] = val;
	++sz;
}
...
TEST(Modifier, PushBack)
{
	vint vec;
	vec.push_back(9);

	EXPECT_EQ(9, vec.at(0));
}
```


### 5. pop_back()
```C++
...
template<class T>
inline void vector<T>::pop_back()
{
	--sz;
	elem[sz].~T();
}
...
TEST(Modifier, PopBack)
{
	vint vec({ 1, 2, 3, 4 });
	int result[3] = { 1, 2, 3 };
	vec.pop_back();

	EXPECT_EQ(3, vec.size());

	for (int i = 0; i < 3; i++) {
		EXPECT_EQ(result[i], vec.at(i));
	}
}
```


### private functions:
```C++
template<class T>
inline void vector<T>::_reallocate() //recreates vector to use new capacity
{
	T* temp = new T[cap];
	std::memcpy(temp, elem, sz * sizeof(T));
	delete[] elem;
	elem = temp;
}

```
---























