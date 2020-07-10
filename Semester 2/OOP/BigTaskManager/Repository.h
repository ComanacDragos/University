#pragma once
#include "Domain.h"

class Repository
{
private:
	std::vector<Task> tasks;
	std::vector<Programmer> programmers;
	std::string taskFile;

public:
	Repository(const std::string& programmersFile, const std::string& taskFile) :taskFile{ taskFile }
	{
		std::ifstream fin{ programmersFile };
		std::string line;

		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->programmers.push_back(Programmer{ tokens[0], stoi(tokens[1]) });
		}

		fin.close();
		fin.open(taskFile, 0);

		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->tasks.push_back(Task{ tokens[0], tokens[1], stoi(tokens[2]) });
		}
		fin.close();
	}

	std::vector<Task> getTasks() { return this->tasks; }
	std::vector<Programmer> getProgrammers() { return this->programmers; }

	void addTask(const Task& task)
	{
		this->tasks.push_back(task);
	}

	//Removes a task with a given description
	void removeTask(const std::string& desc)
	{
		auto it = this->tasks.begin();
		while (it != this->tasks.end())
		{
			if ((*it).getDesc() == desc)
			{
				this->tasks.erase(it);
				break;
			}
			it++;
		}
	}

	void setState(const std::string desc, const std::string status)
	{
		for (Task& task : this->tasks)
		{
			if (task.getDesc() == desc)
			{
				task.setStatus(status);
				break;
			}
		}
	}
	void setProgrammer(const std::string desc, int id)
	{
		for (Task& task : this->tasks)
		{
			if (task.getDesc() == desc)
			{
				task.setProgrammer(id);
				break;
			}
		}
	}

	Task getTask(const std::string& desc)
	{
		for (Task& task : this->tasks)
		{
			if (task.getDesc() == desc)
			{
				return task;
			}
		}
	}

	Programmer getProgrammer(int id)
	{
		for (Programmer& p : this->programmers)
			if (p.getId() == id)
				return p;
	}

	~Repository()
	{
		std::ofstream fout{ this->taskFile };
		for (Task& t : this->tasks)
			fout << t.getDesc() << ',' << t.getStatus() << ',' << std::to_string(t.getId()) << '\n';
		fout.close();
	}

};

