#pragma once
#include "TrenchCoat.h"
#include "Exceptions.h"

class CoatValidator
{
public:
	CoatValidator(){}

	~CoatValidator(){}

	void validateCoat(const std::string& name, const std::string& size, const std::string& source, const std::string& price);

	//empty name is invalid
	std::string validateName(const std::string& name);

	//empty size is invalid
	std::string validateSize(const std::string& size);
	
	//empty source is invalid
	std::string validatePhotographSource(const std::string& source);
	
	//any string that does not represent a natural number is invalid
	std::string validatePrice(const std::string& price);

};

