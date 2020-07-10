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