#pragma once
#include "Repository.h"
#include "Observer.h"

class Service : public Observable
{
private:
	Repository& repo;
public:
	Service(Repository& repo):repo{repo}{}

	std::vector<Issue> getIssues() { return this->repo.getIssues(); }
	std::vector<User> getUsers() { return this->repo.getUsers(); }

	//Adds an issue based on description, status and tester
	void addIssue(const std::string& description, const std::string& status, const std::string& tester);

	void removeIssue(const std::string& description) { 
		this->repo.removeIssue(description);
		this->notify();
	}


	//Sets the solvers name to an issue with the given description
	void resolveIssue(const std::string& description, const std::string& name){
		this->repo.resolveIssue(description, name);
		this->notify();
	}

	~Service() { this->repo.saveIssues(); }
};

