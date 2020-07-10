#pragma once
#include "Domain.h"
#include <fstream>
#include <algorithm>

class Service
{
private:
	std::string file;
	std::vector<Car> cars;

public:
	Service(const std::string& file);

	std::vector<Car> getCars();

	//Calculates the number of cars with a given manufacturer
	//Input: manufacturer - const std::string&
	//Output: number of cars with the given manufacturer
	int nrCars(const std::string& manufacturer);
};

