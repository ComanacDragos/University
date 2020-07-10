#pragma once
#include<fstream>
#include "Vegetable.h"
#include <algorithm>
#include <assert.h>


class Service
{
private:
	std::vector<Vegetable> vegetables;
	std::vector<std::string> families;
	std::string file;

public:
	Service(const std::string& file);

	std::vector<std::string> getFamilies();

	std::vector<Vegetable> getVegetablesFromFamily(const std::string& family);
	
	Vegetable getVegetable(std::string& name);
};


void testService();