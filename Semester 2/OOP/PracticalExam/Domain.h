#pragma once
#include <sstream>
#include <exception>
#include <assert.h>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <fstream>

class Astronomer
{
private:
	std::string name, constelation;
public:
	Astronomer(const std::string& name, const std::string& constelation):name{name},constelation{constelation}{}

	std::string getName() { return this->name; }
	std::string getConstelation() { return this->constelation; }
};

class Star
{
private:
	std::string name, constelation;
	int RA, Dec, diameter;

public:
	Star(const std::string& name, const std::string& constelation, int RA, int Dec, int diameter):name{name}, constelation{constelation}, RA{RA}, Dec{Dec}, diameter{diameter}{}

	std::string getName() { return this->name; }
	std::string getConstelation() { return this->constelation; }

	std::string to_string(char delim)
	{
		return this->name + delim + this->constelation + delim + std::to_string(this->RA) + delim + std::to_string(this->Dec) + delim + std::to_string(this->diameter);
	}
	int getRA() { return this->RA; }
	int getDec() { return this->Dec; }
	int getDiameter() { return this->diameter; }
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

