#pragma once
#include <string.h>
#include <string>
#include <exception>
#include <map>
#include <vector>
#include <exception>

int f(std::vector<int> l)
{
	if (l.size() < 1)
		throw std::exception("Illegal argument");
	std::map<int, int> m;
	for (auto e : l)
	{
		m[e]++;
	}
	int rez{ 0 };
	for (auto e : m) {
		if (e.second > 1)rez++;
	}
	return rez;
}



void test()
{
	try
	{
		f({});
		assert(false);
	}
	catch (std::exception& exc)
	{
		assert(strcmp(exc.what() , "Illegal argument")==0);
	}

	assert(f({ 1,2,3 }) == 0); 
	assert(f({ 1,2,3,1 }) == 1);
	assert(f({ 1,2,3,1,2 }) == 2);
	assert(f({ 1,2,3,1,5,5,2,5 }) == 3);

}


class A
{
public:

	virtual ~A() { std::cout << "~A" << std::endl; }
	virtual void print() { std::cout << "printA" << std::endl; }
};

class B:public A
{
public:
	void print() { std::cout << "printB" << std::endl; }
	
	virtual ~B() {
		std::cout << "~B" << std::endl; }
};
