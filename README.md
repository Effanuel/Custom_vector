# Custom_vector




# Complex

```C++
class Complex {
	double re, im; 
public:
	Complex(double r, double i) :re{ r }, im{ i } {}
	Complex(double r) :re{ r }, im{ 0 } {}
	Complex() :re{ 0 }, im{ 0 } {}

	Complex(const Complex& complex) : re{ complex.re }, im{complex.im} {
		std::cout << "copy" << std::endl;
	}

	double real() const { return re; }
	double imag() const { return im; }
	Complex& operator+=(Complex c) { re += c.re; im += c.im; return *this; }
	
};
```

## 1. Uzd: **a +- bi**

```C++
std::ostream& operator<<(std::ostream& out, const Complex &a) {
	if (a.imag() > 0) {
		out << a.real() << " + " << a.imag() << "i\n";
	}
	else if(a.imag() == 0) {
		out << a.real() << "\n";
	}
	else if (a.real() == 0) {
		out << a.imag() << "i\n";
	}
	else {
		out << a.real() << " - " << -a.imag() << "i\n";
	}	
	return out;
}
```

## 2. Uzd: cin >> **(Input example:  1 -4  )**
```C++
std::istream& operator>>(std::istream& in, Complex &a) {
	double temp1, temp2;
	in >> temp1 >> temp2;
	if (!in.fail()) {
		a.real(temp1); //set
		a.imag(temp2); //set
	} else {
		a.real(0); //set
		a.imag(0); //set
	}
	return in;

}
```

## 3. Uzd: Complex& vs Complex (testavimas su copy constructor'iumi)
```C++
Complex(const Complex& complex) : re{ complex.re }, im{complex.im} {
	std::cout << "copy" << std::endl;
}

int main()
{
	Complex a{ 1, 1 }, b{ 2, 2 };
	a += b; 
	std::cout << a << std::endl;
}
```
---
* CONSOLE OUTPUT:
```C++
Complex& operator+=(Complex c) { re += c.re; im += c.im; return *this; }
```

```
copy
3 + 3i
```
---
* CONSOLE OUTPUT:
```C++
Complex operator+=(Complex c) { re += c.re; im += c.im; return *this; }
```

```
copy
copy
3 + 3i
```
---
## 4. Uzd: **a \*= b**

```C++
Complex& operator*=(Complex c) {
  double temp = (re * c.re) - (im * c.im);
  im = (re * c.im) + (im * c.re);
  re = temp;
  return *this;
}
Complex& operator*=(double c) {
  im *= c;
  re *= c;
  return *this;
}
```
## 5. Uzd: UNARY operator-(Complex a)

```C++
Complex operator-(Complex a) const { 
	Complex temp{ -a.real(), -a.imag() };
	return temp;
}
``




