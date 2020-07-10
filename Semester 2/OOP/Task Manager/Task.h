#pragma once
#include <string>
#include <vector>
#include <sstream>
class Task
{
private:
	std::string description;
	int duration=0, priority=0;

public:
	Task(){}
	Task(const std::string& description, int duration, int priority) :description{ description }, duration{ duration }, priority{ priority }{}
	std::string to_string()
	{
		return this->description + " " + std::to_string(this->priority);
	}
	
	std::string to_file()
	{
		return this->description + " " + " " + std::to_string(this->duration) + std::to_string(this->priority);
	}

	int getDuration() { return this->duration; }
	int getPriority() { return this->priority; }
};


std::vector<std::string> tokenize(const std::string& string, char delimiter);