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
};

