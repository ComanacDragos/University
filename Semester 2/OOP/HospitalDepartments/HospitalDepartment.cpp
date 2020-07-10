#include "HospitalDepartment.h"

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

std::string HospitalDepartment::to_string()
{
	return this->hospitalName + std::to_string(this->numberOfDoctors);
}

std::string NeonatalUnit::to_string()
{
	return this->hospitalName + " " + std::to_string(this->numberOfDoctors) + " Neonatal unit " + std::to_string(this->numberOfMothers) + " " + std::to_string(this->numberOfNewBorns) + " " + double_to_string(this->averageGrade);
}
