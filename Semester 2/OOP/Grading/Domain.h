#pragma once
#include<string>
#include <vector>
#include <sstream>

class User
{
private:
	std::string name, type;
public:
	User(const std::string& name, const std::string& type):name{name},type{type}{}

	std::string getName() { return this->name; }
	std::string getType() { return this->type; }
};

class Issue
{
private:
	std::string description, status, reporter, solver;
public:
	Issue(const std::string& description, const std::string& status, const std::string& reporter, const std::string& solver):description{description}, status{status}, reporter{reporter}, solver{solver}{}

	std::string getDescription() { return this->description; }
	std::string getStatus() { return this->status; }
	
	std::string to_string(char sep)
	{
		return this->description + sep + this->status + sep + this->reporter + sep + this->solver;
	}
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
