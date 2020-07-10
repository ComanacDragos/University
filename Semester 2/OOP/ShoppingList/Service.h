#pragma once
#include <vector>
#include "Item.h"
#include <sstream>
#include <fstream>

class Service
{
private:
	std::vector<Item> items;
	std:: string file;
	void writeToFile();

public:
	Service(const std::string& file);

	std::vector<Item> getItems();

	void deleteItem(std::string name);

	std::vector<Item> filterItems(const std::string& category);

	
};

std::vector<std::string> tokenize(const std::string& string);