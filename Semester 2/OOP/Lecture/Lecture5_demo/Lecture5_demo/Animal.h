#pragma once
#include <string>

class Animal
{
private:
	int a;


protected:
	std::string colour;
	double weight;

public:
	Animal(const std::string& _colour, double _weight);
	virtual ~Animal();

	std::string getColour() const;
	double getWeight() const;

	virtual std::string toString() const;
};

class AnimalToCSV : public Animal
{
public:
	AnimalToCSV(const std::string& color, double weight) :Animal{ color, weight }{}
	~AnimalToCSV(){}
};