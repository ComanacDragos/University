#pragma once
#include "Domain.h"
#include <fstream>

template <typename TElem>
class Repository
{
private:
	std::string file;
	std::vector<TElem> elems;

public:
	Repository(const std::string& file);

	void addElem(TElem& elem);

	void saveToFile();

	std::vector<TElem> getAll();

	void updateScore(TElem& el, int newScore);

	TElem getEl(TElem& el);
};

template<typename TElem>
inline Repository<TElem>::Repository(const std::string& file):file{file}
{
	std::ifstream fin{ this->file };

	std::string line;
	while (std::getline(fin, line))
		this->elems.push_back(TElem{ line });

	fin.close();
}

template<typename TElem>
inline void Repository<TElem>::addElem(TElem& elem)
{
	this->elems.push_back(elem);
}

template<typename TElem>
inline void Repository<TElem>::saveToFile()
{
	std::ofstream fout{ this->file };
	
	for (TElem& elem : this->elems)
		fout << elem.to_string(',') << '\n';
	fout.close();
}

template<typename TElem>
inline std::vector<TElem> Repository<TElem>::getAll()
{
	return this->elems;
}

template<typename TElem>
inline void Repository<TElem>::updateScore(TElem& el, int newScore)
{
	for (TElem& e : this->elems)
		if (e == el)
			e.setScore(newScore);
}

template<typename TElem>
inline TElem Repository<TElem>::getEl(TElem& el)
{
	for (TElem& e : this->elems)
		if (e == el)
			return e;

}

