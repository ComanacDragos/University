#pragma once
#include <string>
#include <stack>
#include "CarList.h"

template <typename TElem>
class Adder
{
private:
	TElem sum;
	std::stack<TElem> elems;

public:
	Adder(const TElem& elem):sum{elem}{}

	TElem suma() { return this->sum; }

	Adder& operator= (Adder& adder)
	{
		if (this == &adder)
			return *this;
		this->sum = adder.sum;
		this->elems = adder.elems;
		return *this;
	}
	
	Adder& operator+(const TElem& elem)
	{
		this->sum += elem;
		this->elems.push(elem);
		return *this;
	}

	Adder& operator++()
	{
		this->sum += this->elems.top();
		this->elems.push(this->elems.top());
		return *this;
	}

	Adder& operator--()
	{
		if (this->elems.empty())
			throw runtime_error{ "No more values" };
		this->sum -= this->elems.top();
		this->elems.pop();
		return *this;
	}

};


void function2()
{
	Adder<int> add{ 5 };
	add = add + 5 + 2;
	++add;

	add + 8;
	std::cout << add.suma()<<'\n';

	--add;
	std::cout << add.suma()<<'\n';

	--(--add);
	std::cout << add.suma() << '\n';

	try
	{
		--(--(--add));
	}
	catch (runtime_error & ex)
	{
		std::cout << ex.what();
	}

}
