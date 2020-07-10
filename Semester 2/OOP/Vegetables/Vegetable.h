#pragma once
#include <string>
#include <vector>
#include <sstream>

class Vegetable
{
private:
	std::string family, name;
	std::vector <std::string> parts;
public:
	Vegetable(){}
	Vegetable(const std::string& family, const std::string& name, const std::vector<std::string>& parts) :family{ family }, name{ name }, parts{ parts }{
}

	std::string getFamily() { return this->family; }
	std::string to_string();
	std::string getName() { return this->name; }
	std::string getParts() {
		std::string parts{ "" };
		for (auto& i : this->parts)
			parts += " " + i;
		return parts;
	}
};

std::vector < std::string> tokenize(const std::string& string, char delimiter);
