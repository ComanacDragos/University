#pragma once

#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <list>
#include <iostream>
using namespace std;

template <typename TElem>
class SmartPointer
{
private:
	TElem* pointer;

public:
	SmartPointer(TElem* pointer=nullptr):pointer{pointer}{}

	SmartPointer<TElem>& operator=(const SmartPointer<TElem>& smartPointer)
	{
		if (this == &smartPointer)
			return *this;

		if(this->pointer!=nullptr)
			delete this->pointer;
		
		this->pointer = smartPointer.pointer;
		return *this;
	}

	bool operator==(const SmartPointer<TElem>& smartPointer)
	{
		return this->pointer == smartPointer.pointer;
	}

	TElem operator*()
	{
		return *this->pointer;
	}

	~SmartPointer() 
	{
		if(this->pointer!=nullptr)
			delete this->pointer; 
	}
};

template <typename TElem>
class Set
{
private:
	std::list<TElem> elems;
public:
	Set(){}

	Set<TElem>& operator+(const TElem& element)
	{
		for (TElem& el : this->elems)
			if (el == element)
				throw std::runtime_error{ "Element already exists" };

		this->elems.push_back(element);
		return *this;
	}

	
	typename Set<TElem>& operator=(Set<TElem>& set)
	{
		if (this == &set)
			return *this;
   		
		this->elems = set.elems;
		return *this;
	}

	Set<TElem>& remove(TElem& element)
	{
		auto it = std::find(this->elems.begin(), this->elems.end(), element);
		if (it != this->elems.end())
			this->elems.erase(it);
		return *this;
	}

	typename std::list<TElem>::iterator begin()
	{
		return this->elems.begin();
	}
	typename std::list<TElem>::iterator end()
	{
		return this->elems.end();
	}

};

