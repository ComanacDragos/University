#pragma once
#include <vector>
#include "Meci.h"
#include <exception>
#include <fstream>
#include <sstream>
#include <stdlib.h>
class Repo
{
private:
	std::vector<Meci> meciuri;

public:
	Repo() {
		std::ifstream fin{ "meciuri.txt" };
		std::string line;

		while (std::getline(fin, line))
		{
			std::string token;
			std::vector<std::string> tokens;
			std::stringstream ss{ line };

			while (std::getline(ss, token, ' '))
			{
				tokens.push_back(token);
			}
			this->meciuri.push_back(Meci{ stoi(tokens[0]), tokens[1], tokens[2], stoi(tokens[3]), stoi(tokens[4]) });
		}
	}

	void addMeci(Meci& meci);

	std::vector<Meci> getMeciuri();
};

