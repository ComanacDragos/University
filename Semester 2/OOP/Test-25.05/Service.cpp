#include "Service.h"

Service::Service(const std::string& file):file{file}
{
	std::ifstream fin{ this->file };
	std::string line;
	while (std::getline(fin, line))
	{
		std::vector<std::string> tokens = tokenize(line, '|');
		Car car{ tokens[0], tokens[1], tokens[3], stoi(tokens[2]) };
		this->cars.push_back(car);
	}
	std::sort(this->cars.begin(), this->cars.end());
	fin.close();
}

std::vector<Car> Service::getCars()
{
	return this->cars;
}

int Service::nrCars(const std::string& manufacturer)
{
	int cars = 0;
	for (Car& car : this->cars)
		if (car.getManufacturer() == manufacturer)
			cars += 1;
	return cars;
}

