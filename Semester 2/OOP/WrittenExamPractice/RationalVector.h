#pragma once
#include <string>
#include <vector>
#include <assert.h>
#include <iostream>
#include <ostream>
#include "CarList.h"
#include <sstream>

/*class runtime_error : public std::exception
{
private:
	std::string message;

public:
	runtime_error(const std::string& s) : message{ s } {}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};
*/
class Rational
{
	friend std::ostream& operator<<(std::ostream& ostream, Rational& r);
private:
	int numerator, denominator;
public:
	Rational() :numerator{ 0 }, denominator{ 1 }{}
	Rational(int a, int b) :numerator{ a }, denominator{ b }{}
	Rational(const Rational& r)
	{
		this->numerator = r.numerator;
		this->denominator = r.denominator;
	}
	int getNumerator() { return this->numerator; }
	int getDenominator() { return this->denominator; }

	bool operator==(Rational& r) {
		return this->numerator == r.numerator && this->denominator == r.denominator;
	}

	Rational operator/(Rational& r1)
	{
		if (r1.getNumerator() == 0)
			throw runtime_error{ "Division by zero!" };
		return Rational{ this->numerator * r1.denominator, this->denominator * r1.numerator };
	}
};

std::ostream& operator<<(std::ostream& o, Rational& r) 
{
	o << r.getNumerator() << '/' << r.getDenominator();
	return o;
}

/*
template <typename T>
class Vector
{
private:
	std::vector<T> v;
public:
	Vector(std::vector<T> vector):v{vector}{}

	void printAll(std::ostream& o)
	{
		for (T& t : this->v)
			o << t << ", ";
		o << '\n';
	}
};


void rational()
{
	Rational a{}, b{ 6,15 }, c{ 3,5 }, d{ b };

	assert(a.getNumerator() == 0);
	assert(c.getDenominator() == 5);

	assert(b == d);
	Rational res1 = b / c;
	std::cout << res1 << '\n';

	try {
		Rational re2 = b / a;
	}
	catch (runtime_error & e)
	{
		assert(strcmp(e.what(), "Division by zero!") == 0);
	}
	Vector<int> v1{ std::vector<int>{1,2,3} };
	v1.printAll(std::cout);

	Vector<Rational> v2{ std::vector<Rational>{a,b,c,d} };
	v2.printAll(std::cout);

}*/
