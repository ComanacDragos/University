#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class Bill
{
private:
	std::string name, code;
	double sum;
	bool isPaid;
public:
	Bill(const std::string& name, const std::string& code, double sum, bool isPaid) :name{ name }, code{ code }, sum{ sum }, isPaid{ isPaid }{}

	std::string to_string();
	double getSum() { return this->sum; }
	bool getIsPaid() { return this->isPaid; }
	std::string getCompany() const { return this->name; }
	bool operator<(const Bill& bill) {
		return this->name < bill.name;
	}
	bool operator==(const Bill& bill) {
		return this->name == bill.name;
	}
};

std::vector<std::string> tokenize(const std::string& string, char delimiter);

std::string double_to_string(double n);