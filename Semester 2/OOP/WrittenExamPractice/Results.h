#pragma once
#include <iostream>
/*
class B
{
public:
	B() { std::cout << "B{}"; }

	virtual void print() { std::cout << "B"; }
	virtual ~B() { std::cout << "~B()"; }
};

class D :public B
{
public:
	D() { std::cout << "D{}"; }
	void print()override { std::cout << "D"; }
	virtual ~D() { std::cout << "~D()"; }
};
*/
class Person
{
public:
	virtual void print() = 0;
};


class E
{
public:
	E() { std::cout << "E{}"; }
	virtual ~E() { std::cout << "~E{}"; }
};

class DE :public E
{
public:
	static int n;
	DE() { n++; }

};
int DE::n = 0;

int fct2(int x)
{
	if (x < 0)
	{
		throw E{};
		std::cout << "nr less than 0";
	}
	else if (x == 0)
	{
		throw DE{};
		std::cout << "nr eq to 0";
	}
	return x % 10;
}