#pragma once
#include <sstream>
#include <exception>
#include <assert.h>
#include <string>
#include <vector>
#include <iomanip>

class Car
{
private:
	std::string manufacturerName, model, color;
	int year;

public:
	Car(const std::string& manufacturer, const std::string& model, const std::string& color, int year);

	std::string to_string();

	std::string getManufacturer() { return this->manufacturerName; }
	std::string getModel() { return this->model; }
	std::string getColor() { return this->color; }

	bool operator<(const Car& car);
	bool operator==(const Car& car);

};

class Exceptions : public std::exception
{
private:
	std::string message;

public:
	Exceptions(const std::string& s) : message{ s } {}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};

std::vector < std::string> tokenize(const std::string& string, char delimiter);
std::string double_to_string(double n);