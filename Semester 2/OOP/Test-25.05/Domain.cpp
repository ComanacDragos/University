#include "Domain.h"

std::vector<std::string> tokenize(const std::string& string, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss{ string };
	std::string token;
	while (std::getline(ss, token, delimiter))
		tokens.push_back(token);
	return tokens;
}

std::string double_to_string(double n)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << n;

	std::string s;
	ss >> s;
	return s;
}

Car::Car(const std::string& manufacturer, const std::string& model, const std::string& color, int year):manufacturerName{manufacturer}, model{model}, color{color}, year{year}
{

}

std::string Car::to_string()
{
	return this->manufacturerName + " " + this->model;
}

bool Car::operator<(const Car& car)
{
	return this->manufacturerName < car.manufacturerName;
}

bool Car::operator==(const Car& car)
{
	return this->manufacturerName == car.manufacturerName;
}
