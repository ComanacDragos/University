#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>

template <typename TElem>
class Carnet
{
private:
	std::vector<std::pair<std::string, TElem>> pairs;
public:

	Carnet(){}

	Carnet& add(const std::string& materie, const TElem& elem)
	{
		this->pairs.push_back(std::make_pair(materie, elem));
		return *this;
	}

	TElem& operator[](const std::string& materie)
	{
		for (std::pair<std::string, TElem>& p : this->pairs)
			if (p.first == materie)
				return p.second;
		throw std::exception{ "Nu exista materia" };
	}
	Carnet& removeLast()
	{
		this->pairs.pop_back();
		return *this;
	}

};


void anScolar()
{
	Carnet<int> cat;
	cat.add("SDA", 9);
	cat.add("OOP", 7).add("FP", 10);
	std::cout << cat["OOP"];
	cat.removeLast().removeLast();
	try
	{
		std::cout << cat["OOP"]<<'\n';
	}
	catch(std::exception& ex)
	{
		std::cout << "Nu exista nota la oop\n";
	}
}