#pragma once
#include <string>
#include <chrono>
class User
{
private:
	std::string uniqueUserName, name;
public:
	User(const std::string& unique, const std::string& Name) :uniqueUserName{ unique }, name{ Name }{}

	std::string getName() { return this->name; };

	std::string getUniqueName() { return this->uniqueUserName; };
};

class Message
{
private:
	std::string message;
public:
	Message(const std::string& message) :message{ message }{}
	std::string getMessage() { return this->message; };
};

