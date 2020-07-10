#pragma once
#include <iostream>
#include <sstream>
#include "Service.h"
#include <fstream>

class UI
{
private:
	Service srv;

public:
	void startProgram();

	void add(const std::vector<std::string>& params);

	void list(const std::vector<std::string>& params);

	void listEfficient(const std::vector<std::string>& params);

	void fileLocation(const std::vector<std::string>& params, std::string filepath);

};

