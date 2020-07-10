#pragma once
#include <string>
#include <vector>
#include <utility>
#include <iostream>


template <typename TElem>
class Expresie
{
private:
	TElem elem;
	std::vector<TElem> undoStack;

public:
	Expresie(const TElem& elem) {
		this->elem = elem;
	}
	TElem valoare() {
		return this->elem;
	}

	Expresie& operator=(const Expresie& expr) {
		if (this == &expr)
			return *this;

		this->elem = expr.elem;
		this->undoStack = expr.undoStack;

		return *this;
	}

	Expresie& operator+(const TElem& el) {
		this->undoStack.push_back(this->elem);
		this->elem += el;
		return *this;
	}

	Expresie& operator-(const TElem& el) {
		this->undoStack.push_back(this->elem);
		this->elem -= el;
		return *this;
	}

	Expresie& undo(){
		this->elem = *(this->undoStack.end()-1);
		this->undoStack.pop_back();
		return *this;
	}

};

void operatii()
{
	Expresie<int> exp{ 3 };
	
	exp = exp + 3 + 7;
	
	exp = exp - 8;
	std::cout << exp.valoare()<<'\n';
	exp.undo();
	std::cout << exp.valoare() << '\n';
	exp.undo().undo();
	std::cout << exp.valoare() << '\n';

}