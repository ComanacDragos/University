#pragma once
#include <string>
#include <sstream>
#include <vector>

class Question
{
private:
	int id, score;
	std::string text, answer;

public:
	Question(int id, const std::string& text, const std::string& answer, int score) :id{ id }, text{ text }, answer{ answer }, score{score}{}

	int getId() { return this->id; }
	int getScore() { return this->score; }
	std::string getText() { return this->text; }
	std::string getAnswer() { return this->answer; }

	std::string to_string() { return std::to_string(this->id) + "," + this->text + "," + this->answer + "," + std::to_string(this->score); }
};

class Participant
{
private:
	int score;
	std::string name;
	std::vector<int> answeredQuestions;
public:
	Participant(std::string& name, int score):name{name}, score{score}{}

	int getScore() { return this->score; }
	void setScore(int newScore) { this->score = newScore; }
	std::string getName() { return this->name; }

	void answer(int id) { this->answeredQuestions.push_back(id); }

	bool isAnswered(int id) {
		auto  it = std::find(this->answeredQuestions.begin(), this->answeredQuestions.end(), id);
		if (it != this->answeredQuestions.end())
			return true;
		return false;
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
