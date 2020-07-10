#include "Domain.h"

std::vector<std::string> tokenize(const std::string& string, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss{ string };
	std::string token;
	while (std::getline(ss, token, delimiter))
		tokens.push_back(token);
	return tokens;
}

Question::Question(const std::string& info)
{
	std::vector<std::string> tokens = tokenize(info,',');
	this->id = stoi(tokens[0]);
	this->text = tokens[1];
	this->answer = tokens[2];
	this->score = stoi(tokens[3]);
}

Question::Question(int id, const std::string& text, const std::string& answer, int score):id{id}, text{text}, answer{answer}, score{score}
{
}

std::string Question::to_string(char delimiter)
{
	return std::to_string(this->id) + delimiter + this->text + delimiter + this->answer + delimiter + std::to_string(this->score);
}

Participant::Participant(const std::string& info)
{
	std::vector<std::string> tokens = tokenize(info, ',');
	this->name = tokens[0];
	this->score = stoi(tokens[1]);
}

std::string Participant::to_string(char delimiter)
{
	return this->name + delimiter + std::to_string(this->score);
}
