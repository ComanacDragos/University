#pragma once
#include <stack>
#include <iostream>

/*
template <typename TElem>
class Adder
{
private:
	TElem sum;
	std::stack<TElem> stack;
public:
	Adder(const TElem& elem):sum{elem}{}

	Adder& operator=(const Adder& a)
	{
		if (this == &a)
			return *this;
		this->sum = a.sum;
		this->stack = a.stack;
	
		return *this;
	}

	Adder& operator+(const TElem& elem)
	{
		this->stack.push(this->sum);
		this->sum = this->sum + elem;
		return *this;
	}
	TElem& suma()
	{
		return this->sum;
	}

	//prefix
	Adder& operator--()
	{
		this->sum = this->stack.top();
		this->stack.pop();
		return *this;
	}

	//postfix
	Adder& operator--(int)
	{

		Adder& temp = *this;
		this->sum = this->stack.top();
		this->stack.pop();
		return temp;
	}


};

void adder()
{

	Adder<int> add{ 1 };
	add = add + 7 + 3;
	add + 8;
	std::cout << add.suma()<<'\n';
	add--;
	std::cout << add.suma() << '\n';
	--add--;
	std::cout << add.suma() << '\n';


}	*/