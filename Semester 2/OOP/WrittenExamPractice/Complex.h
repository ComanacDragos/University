#pragma once
#include <string>
#include "CarList.h"
/*
class runtime_error
{
	
private:
	std::string msg;
public:
	runtime_error(const std::string& msg):msg{msg}{}

	std::string what() { return this->msg; }
};
*/

class Complex
{
	friend std::ostream& operator<<(std::ostream& o, const Complex& c);
private:
	int real, imaginary;

public:

	Complex(int real=0, int imaginary=0):real{real}, imaginary{imaginary}{}

	Complex(const Complex& c)
	{
		this->real = c.real;
		this->imaginary = c.imaginary;
	}
	int gerReal() { return this->real; }
	int getImaginary() { return this->imaginary; }

	bool operator==(const Complex& c) { return this->real == c.real && this->imaginary == c.imaginary; }

	Complex& operator=(const Complex& c)
	{
		if (this == &c)
			return *this;
		this->real = c.real;
		this->imaginary = c.imaginary;
		return *this;
	}

	Complex operator/(int nr)
	{
		if (nr == 0)
			throw runtime_error{ "Division by zero!" };
		return Complex{ this->real / nr, this->imaginary / nr };
	}

};

std::ostream& operator<<(std::ostream& o, const Complex& nr)
{
	o << nr.real << "+" << nr.imaginary<<'i';
	return o;
}

template <typename TElem>
class Vector
{
private:
	std::vector<TElem> elems;
public:
	Vector(std::vector<TElem> elems):elems{elems}{}

	void printAll(std::ostream& o)
	{
		for (TElem& e : this->elems)
			o << e << ", ";
	}
};

void complex()
{
	Complex a{}, b{ 1,2 }, c{ 6,4 }, d{ b };

	assert(a.gerReal() == 0 && a.getImaginary() == 0);

	assert(c.getImaginary() == 4);

	assert(b == d);

	Complex res1 = c / 2;
	std::cout << res1 << "\n";
	try
	{
		Complex res2 = b / 0;
	}
	catch (runtime_error & e)
	{
		assert(true);
	}
	Vector<std::string> v1{ std::vector<std::string>{"a","b"} };
	v1.printAll(std::cout);

	Vector<Complex> v2{ std::vector<Complex>{a,b,c,d} };
	v2.printAll(std::cout);

}