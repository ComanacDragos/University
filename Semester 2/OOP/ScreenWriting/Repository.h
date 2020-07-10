#pragma once
#include "Domain.h"
#include <assert.h>

class Repository
{
private:
	std::vector<Writer> writers;
	std::vector<Idea> ideeas;

public:
	Repository(const std::string& writersFile, const std::string& ideeasFile)
	{
		std::ifstream finW{ writersFile };
		std::string line;
		while (std::getline(finW, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->writers.push_back(Writer{ tokens[0], tokens[1] });
		}
		finW.close();
		std::ifstream finI{ ideeasFile };

		while (std::getline(finI, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->ideeas.push_back(Idea{ tokens[0], tokens[1],tokens[2], stoi(tokens[3]) });
		}
	}

	std::vector<Writer> getWriters() { return this->writers; }
	std::vector<Idea> getIdeeas() { return this->ideeas; }


	//Adds an Idea to the vector of ideeas
	void addIdeea(Idea& idea)
	{
		for (Idea& i : this->ideeas)
		{
			if (idea.getAct() == i.getAct() && idea.getDesc() == i.getDesc())
				throw MyException{ "Existent idea" };
		}
		this->ideeas.push_back(idea);
	}

	//Sets the status of the given idea to accepted
	void acceptIdea(Idea& idea)
	{
		for (Idea& i : this->ideeas)
			if (idea.getAct() == i.getAct() && idea.getDesc() == i.getDesc())
			{
				i.accept();
			}
	}
};

void testAddIdeea();
void testAcceptIdea();