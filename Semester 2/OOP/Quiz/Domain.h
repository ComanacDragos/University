#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <exception>

std::vector<std::string> tokenize(const std::string& string, char delimiter);

class Question
{
private:
	int id, score;
	std::string text, answer;

public:
	Question(const std::string& info);
	Question(int id, const std::string& text, const std::string& answer, int score);
	int getId() { return this->id; }
	int getScore() { return this->score; }
	std::string getText() {	return this->text; }
	std::string getAnswer() { return this->answer; }

	bool operator==(const Question& q) { return this->id == q.id; }
	bool operator <(const Question& q) { return this->id < q.id; }

	std::string to_string(char delimiter);

	void setScore(int newScore) { this->score = newScore; }
};

class Participant
{
private:
	int score;
	std::string name;
public:
	Participant(const std::string& info);
	Participant(const std::string& name, int score):name{name}, score{score}{}
	int getScore() { return this->score; }
	std::string getId() { return this->name; }
	std::string getName() { return this->name; }
	std::string to_string(char delimiter);

	void setScore(int newScore) { this->score = newScore; }

	bool operator==(const Participant& p) { return this->name == p.name; }
};

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
