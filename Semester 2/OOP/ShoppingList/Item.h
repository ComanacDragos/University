#pragma once
#include <string>
class Item
{
private:
	std::string category, name;
	int quantity;

public:
	Item(const std::string& name, const std::string& category, int quantity):category{category},name{name}, quantity{quantity}{}

	std::string to_string() {
		return this->name + "," + this->category + "," + std::to_string(this->quantity);
	}

	std::string getName() { return this->name; }
	std::string getCategory() { return this->category; }
	int getQuantity() { return this->quantity; }

	bool operator==(const Item& item) {
		return this->name == item.name;
	}
};

