#pragma once
#include <fstream>
#include "Task.h"
#include <algorithm>
#include <assert.h>
class Service
{
private:
	std::vector<Task> tasks;
	std::string file;

public:
	Service(const std::string& file) :file{ file }
	{
		std::ifstream fin{ file };
		std::string line;
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ' ');
			Task task{ tokens[0], stoi(tokens[1]), stoi(tokens[2]) };
			this->tasks.push_back(task);
		}
		std::sort(this->tasks.begin(), this->tasks.end(), [](Task t1, Task t2) {return t1.getPriority() < t2.getPriority(); });
		fin.close();
		
	}

	std::vector<Task> getTasks() { return this->tasks; }


	//returns the sum of the duration of tasks with given priority
	int totalTime(int priority)
	{
		int time = 0;
		for (Task& task : this->tasks)
		{
			if (task.getPriority() == priority)
				time += task.getDuration();
		}
		return time;
	}
};

void testService();