#pragma once
#include "Domain.h"
#include <fstream>
#include <algorithm>
#include <assert.h>

class Repository
{
private:
	std::vector<Issue> issues;
	std::vector<User> users;

	std::string issueFile;
public:
	Repository(const std::string& issueFile, const std::string& usersFile) :issueFile{ issueFile }
	{
		std::ifstream fin{ usersFile };
		std::string line;
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line,',');
			this->users.push_back(User{ tokens[0], tokens[1] });
		}
		fin.close();
		
		fin.open(this->issueFile, 0);
		
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->issues.push_back(Issue{ tokens[0], tokens[1], tokens[2], tokens[3] });
		}
		fin.close();
	}

	void saveIssues()
	{
		std::ofstream fout{ this->issueFile };
		for (Issue& i : this->issues)
		{
			fout << i.to_string(',') << '\n';
		}
		fout.close();
	}

	std::vector<Issue> getIssues() { return this->issues; }
	std::vector<User> getUsers() { return this->users; }

	//Adds an issue based on description, status and tester
	void addIssue(Issue& issue)
	{
		for (Issue& i : this->issues)
		{
			if (i.getDescription() == issue.getDescription())
				throw MyException{ "Issue already exists" };
		}
		this->issues.push_back(issue);
	}

	Issue getIssue(const std::string& description)
	{
		for (Issue& i : this->issues)
		{
			if (i.getDescription() == description)
				return i;
		}
	}

	void removeIssue(const std::string& description)
	{
		//std::remove_if(this->issues.begin(), this->issues.end(), [description](Issue& i1) {return i1.getDescription() == description && i1.getStatus()=="closed"; });
		//this->issues.shrink_to_fit();
		auto it = this->issues.begin();
		while (it != this->issues.end())
		{
			Issue i = *it;
			if (i.getDescription() == description && i.getStatus() == "closed")
			{
				this->issues.erase(it);
				return;
			}
			it++;
		}
	}

	//Sets the solvers name to an issue with the given description
	void resolveIssue(const std::string& description, const std::string& name)
	{
		for (Issue& i : this->issues)
			if (i.getDescription() == description)
			{
				i.setSolver(name);
				return;
			}
	}
};


void TestRepo();
void TestResolve();