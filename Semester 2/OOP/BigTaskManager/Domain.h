#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

class Programmer
{
private:
	std::string name;
	int id;
public:
	Programmer(const std::string& name, int id):name{name}, id{id}{}

	std::string getName() { return this->name; }
	int getId() { return this->id; }
};

class Task
{
private:
	int id;
	std::string desc, status;

public:
	Task(const std::string& desc, const std::string& status, int id=-1):id{id}, desc{desc}, status{status}{}

	int getId() { return this->id; }
	std::string getStatus() { return this->status; }
	std::string getDesc() { return this->desc; }

	void setStatus(const std::string& status) { this->status = status; }
	void setProgrammer(int id) { this->id = id; }

};


std::vector<std::string> tokenize(const std::string& string, char delimiter);

class MyException : public std::exception
{
private:
	std::string message;

public:
	MyException(const std::string& s) : message{ s } {}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};
