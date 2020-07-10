#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>


class Question
{
private:
	int id;
	std::string text, name;

public:
	Question(int id, const std::string& text, const std::string& name):id{id}, text{text},name{name}{}
	Question(){}
	int getId() { return this->id; }
	std::string getText() { return this->text; }
	std::string getName() { return this->name; }

	std::string to_string(char delim)
	{
		return std::to_string(this->id) + delim + this->text + delim + this->name;
	}
};

class Answer
{
private:
	int id, qid, votes;
	std::string name, text;
public:
	Answer(int id,int qid, const std::string& name, const std::string& text, int votes=0):id{id},qid{qid}, name{name}, text{text}, votes{votes}{}

	int getId() { return this->id; }
	int getQId() { return this->qid; }
	std::string getName() { return this->name; }
	std::string getText() { return this->text; }
	int getVotes() { return this->votes; }

	void setVotes(int newVotes)
	{
		this->votes = newVotes;
	}

	std::string to_string(char delim)
	{
		return std::to_string(this->id) + delim + std::to_string(this->qid) + delim + this->name + delim + this->text + delim + std::to_string(this->votes);
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
