#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class Question
{
private:
	int id;
	std::string text, name;
public:
	Question(int id, const std::string& text, const std::string& name):id{id}, text{text},name{name}{}

	int getId() { return this->id; }
	std::string to_string(char delim)
	{
		return std::to_string(this->id) + delim + this->text + delim + this->name;
	}

	std::string getText() { return this->text;}
};

class Answer
{
private:
	int id, qid, votes;
	std::string user, text;

public:
	Answer(int id, int qid, const std::string& user, const std::string& text, int votes):id{id},qid{qid}, user{user}, text{text}, votes{votes}{}

	int getId() { return this->id; }
	int getQId() { return this->qid; }

	int getVotes() { return this->votes; }
	void upVote() { this->votes++; }
	void downVote() { this->votes--; }

	std::string getUser() { return this->user; }
	std::string to_string(char delim)
	{
		return std::to_string(this->id)+delim+ this->user + delim + this->text + delim + std::to_string(this->votes);
	}

	void setVotes(int votes)
	{
		this->votes = votes;
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
