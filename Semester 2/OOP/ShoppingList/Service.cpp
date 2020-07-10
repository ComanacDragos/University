#include "Service.h"

void Service::writeToFile()
{
	std::ofstream fout(this->file);
	for (auto& i : this->items)
		fout << i.to_string()<<'\n';
	fout.close();
}

Service::Service(const std::string& file)
{
	this->file = file;
	std::ifstream fin{ file };
	std::string line;
	while (std::getline(fin, line))
	{
		std::vector<std::string> tokens = tokenize(line);
		this->items.push_back(Item{ tokens[0], tokens[1], stoi(tokens[2]) });
	}
	fin.close();
}

std::vector<Item> Service::getItems()
{
	return this->items;
}

//Deletes a given item
void Service::deleteItem(std::string name)
{
	Item item{ name, "",-1 };
	auto it = std::find(this->items.begin(), this->items.end(), item);
	if (it == this->items.end())
		throw std::exception{ "Item does not exist" };
	this->items.erase(it);
	this->writeToFile();
}

std::vector<Item> Service::filterItems(const std::string& category)
{
	std::vector<Item> filteredItems;
	for (Item& i : this->items)
	{
		if (i.getCategory() == category)
			filteredItems.push_back(i);
	}
	return filteredItems;
}

std::vector<std::string> tokenize(const std::string& string)
{
	std::vector<std::string> tokens;
	std::stringstream ss{ string };
	std::string token;
	while (std::getline(ss, token, ','))
		tokens.push_back(token);
	return tokens;
}
