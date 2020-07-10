#include "Service.h"

Service::Service(const std::string& file):file{file}
{
	std::ifstream fin{ this->file };
	std::string line;
	while (std::getline(fin, line))
	{
		std::vector<std::string> tokens = tokenize(line, ';');
		
		if (tokens[3] == "false")
			this->bills.push_back(Bill{ tokens[0], tokens[1], stod(tokens[2]), false });
		else
			this->bills.push_back(Bill{ tokens[0], tokens[1], stod(tokens[2]), true });
	}
}

std::vector<Bill> Service::getBills()
{
	return this->bills;
}


void Service::sort()
{
	std::sort(this->bills.begin(), this->bills.end());//, [](Bill b1, Bill b2) {return b1.getCompany() <= b2.getCompany(); });
}

int Service::calculateTotal(const std::string& company)
{
	double total = 0;
	for (Bill& b : this->bills)
	{
		if (b.getCompany() == company && !b.getIsPaid())
		{
			total += b.getSum();
		}
	}
	return total;
}
