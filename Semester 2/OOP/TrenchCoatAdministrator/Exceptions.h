#pragma once
#include <string>

class Exceptions : public std::exception
{
private:
	std::string message;

public:
	Exceptions(const std::string& s) : message{ s } {}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};

class ExistentTrenchCoat : public Exceptions
{
public:
	ExistentTrenchCoat(const std::string& message):  Exceptions{message}{}
};

class InexistentTrenchCoat : public Exceptions
{
public:
	InexistentTrenchCoat(const std::string& message): Exceptions{message}{}
};


class BadPosition : public Exceptions
{
public:
	BadPosition(const std::string& message) : Exceptions{ message } {}
};

class InvalidCoat : public Exceptions
{
public:
	InvalidCoat(const std::string& message): Exceptions{message}{}
};

class UndoException :public Exceptions
{
public:
	UndoException(const std::string& message) : Exceptions{ message } {}
};