#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

class Student
{
private:
	std::string id, name, email, teacher, title;
	int year;
public:
	Student(const std::string& id, const std::string&name, const std::string& email, int year, const std::string& thesis, const std::string& coordinator):id{id}, name{name}, email{email}, teacher{coordinator}, title{thesis},year{year}{}
	
	std::string to_string(char delim)
	{
		return this->id + delim + this->name + delim + this->email + delim + std::to_string(this->year) + delim + this->title + delim + this->teacher;
	}

	std::string getId() { return this->id; }
	int getYear() const { return this->year; } 
	std::string getTeacher() { return this->teacher; }
	std::string getName() { return this->name; }
	std::string getEmail() { return this->email; }
	std::string getThesis() { return this->title; }

	void setThesis(const std::string& newTitle) { this->title = newTitle; }
	void setEmail(const std::string& newEmail) { this->email = newEmail; }
	void setTeacher(const std::string& newTeacher) { this->teacher = newTeacher; }
};

std::vector<std::string> tokenize(const std::string& string, char delimiter);

class Exception : public std::exception
{
private:
	std::string message;

public:
	Exception(const std::string& s) : message{ s } {}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};
