#pragma once
#include <iostream>
#include <string>
#include <vector>

template <typename TElem>
class Catalog
{
private:
	std::string materie;
	std::vector<TElem> elems;
public:
	Catalog(const std::string& materie) :materie{ materie }{}

	Catalog& operator+(const TElem& elem)
	{
		this->elems.push_back(elem);
		return *this;
	}

	Catalog& operator=(const Catalog& c)
	{
		if (this == &c)
			return *this;
		this->materie = c.materie;
		this->elems = c.elems;
		
		return *this;
	}

	typename std::vector<TElem>::iterator begin() { return this->elems.begin(); }
	typename std::vector<TElem>::iterator end() { return this->elems.end(); }
};

void catalog()
{
	Catalog<int> cat{ "OOP" };
	cat + 10;
	cat = cat + 8 + 6;
	int sum = 0;
	for (auto n : cat) {
		sum += n;
	}
	std::cout << "Suma note: " << sum << '\n';
}