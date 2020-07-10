#include "CoatValidator.h"

void CoatValidator::validateCoat(const std::string& name, const std::string& size, const std::string& source, const std::string& price)
{
	std::string errorMessage{ "" };
	errorMessage += this->validateName(name);
	errorMessage += this->validateSize(size);
	errorMessage += this->validatePhotographSource(source);
	errorMessage += this->validatePrice(price);

	if (errorMessage.size() != 0)
		throw InvalidCoat{ errorMessage };
}

std::string CoatValidator::validateName(const std::string& name)
{
	std::string errorMessage{ "" };
	if (name.size() == 0)
		errorMessage = "Name is empty\n";
	
	return errorMessage;
}

std::string CoatValidator::validateSize(const std::string& size)
{
	std::string errorMessage ={ "" };
	if (size.size() == 0)
		errorMessage = "Size is empty\n";

	return errorMessage;
}

std::string CoatValidator::validatePhotographSource(const std::string& source)
{
	std::string errorMessage{ "" };
	if (source.size() == 0)
		errorMessage = "Photograph source is empty\n";

	return errorMessage;
}

std::string CoatValidator::validatePrice(const std::string& price)
{
	std::string errorMessage{ "" };

	if (price.size() == 0)
	{
		errorMessage = "The price is empty\n";
		return errorMessage;
	}

	for (auto iterator : price)
		if (isdigit(iterator) == false)
		{
			errorMessage = "The price is not a natural number\n";
		}
	return errorMessage;
}

