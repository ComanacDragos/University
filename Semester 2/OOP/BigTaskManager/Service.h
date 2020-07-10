#pragma once
#include "Repository.h"
#include "Observer.h"

class Service : public Observable
{
private:
	Repository& repo;

public:
	Service(Repository& repo) :repo{ repo } {}

	std::vector<Task> getTasks() { return this->repo.getTasks(); }
	std::vector<Programmer> getProgrammers() { return this->repo.getProgrammers(); }

	void addTask(const std::string& desc, const std::string status, int id=-1)
	{
		this->repo.addTask(Task{ desc,status,id });
		this->notify();
	}

	//Removes a task with a given description
	void removeTask(const std::string& desc)
	{
		this->repo.removeTask(desc);
		this->notify();
	}

	//Starts the task by updating the status and the programmer id of a task identified by a given description
	void startTask(const std::string& desc, const std::string& status, int id)
	{
		if (status != "open")
			throw MyException{ "Task not open" };

		this->repo.setState(desc, "inProgress");
		this->repo.setProgrammer(desc, id);
		this->notify();
	}

	void closeTask(const std::string& desc, const std::string& status, int id)
	{
		if (status != "inProgress" || id != this->repo.getTask(desc).getId())
			return;
		this->repo.setState(desc, "closed");
		this->notify();
	}

	Programmer getProgrammer(int id)
	{
		return this->repo.getProgrammer(id);
	}
};

