#pragma once
#include "Domain.h"
#include <fstream>

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
	
};

