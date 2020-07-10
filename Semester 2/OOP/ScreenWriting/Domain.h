#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class Writer
{
private:
	std::string name, expertise;
public:
	Writer(const std::string& name, const std::string& expertise):name{name}, expertise{expertise}{}

	std::string getName() { return this->name; }
	std::string getExpertise() { return this->expertise; }

	std::string to_string(char delim) { return this->name + delim + this->expertise; }
};

class Idea
{
private:
	std::string desc, status, creator;
	int act;

public:
	Idea(const std::string& desc, const std::string& status, const std::string& creator, int act):desc{desc}, status{status}, creator{creator},act{act}{}

	std::string getDesc() { return this->desc; }
	std::string getCreator() { return this->creator; }
	std::string getStatus() { return this->status; }
	int getAct() { return this->act; }

	void accept() { this->status = "accepted"; }

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
