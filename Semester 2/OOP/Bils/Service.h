#pragma once
#include <fstream>
#include "Bill.h"
#include <algorithm>

class Service
{
private:
	std::vector<Bill> bills;
	std::string file;
public:
	Service(const std::string& file);

	std::vector<Bill> getBills();

	void sort();

	int calculateTotal(const std::string& company);
};

