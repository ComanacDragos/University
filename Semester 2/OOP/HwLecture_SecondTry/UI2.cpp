#include "UI2.h"

std::vector<std::string> tokenize(std::string string, const char delimiter)
{
	std::vector<std::string> result;

	std::stringstream stringStream{ string };
	std::string token;

	while (std::getline(stringStream, token, delimiter))
		if (token.size() != 0)
		{
			std::stringstream tokenStringStream{ token };
			while (std::getline(tokenStringStream, token, ' '))
				if (token.size() != 0)
					result.push_back(token);
		}

	return result;
}

void UI2::start()
{
	while (1)
	{
		std::string userInput;
		std::getline(std::cin, userInput);

		if (userInput == "exit")
			return;


	}
}

void UI2::addHelicopter(std::vector<std::string> parameters)
{
}

void UI2::addPlane(std::vector<std::string> parameters)
{
}

void UI2::addBalloon(std::vector<std::string> parameters)
{
}

void UI2::showModels(std::vector<std::string> parameters)
{
}

void UI2::showAltitudes(std::vector<std::string> parameters)
{
}
