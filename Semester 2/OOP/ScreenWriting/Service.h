#pragma once
#include "Repository.h"
#include "Observer.h"

class Service : public Observable
{
private:
	Repository& repo;
public:
	Service(Repository& repo):repo{repo}{}

	std::vector<Writer> getWriters() { return this->repo.getWriters(); }
	std::vector<Idea> getIdeeas() { return this->repo.getIdeeas(); }

	std::vector<Idea> getSortedIdeeas()
	{
		std::vector<Idea> ideeas = this->repo.getIdeeas();
		std::sort(ideeas.begin(), ideeas.end(), [](Idea& i1, Idea& i2) {return i1.getAct() < i2.getAct(); });
		return ideeas;
	}

	void addIdea(const std::string& desc, const std::string& status, const std::string& creator, int act)
	{
		if (desc.size() == 0)
			throw MyException{ "Desc is empty" };
		if (act != 1 && act != 2 && act != 3)
			throw MyException{ "Act not 1 2 3" };
		this->repo.addIdeea(Idea{ desc,status, creator, act });
	}

	void acceptIdea(const std::string& desc, const std::string& status, const std::string& creator, int act)
	{

		this->repo.acceptIdea(Idea{ desc,status, creator, act });
		this->notify();
	}

	std::vector<Idea> getAcceptedIdeeas(const std::string& name)
	{
		std::vector<Idea> ideeas;
		for (Idea& i : this->repo.getIdeeas())
		{
			if (i.getCreator() == name && i.getStatus() == "accepted")
				ideeas.push_back(i);
		}

		return ideeas;
	}

	std::vector<Idea> getAllAcceptedIdeeasOnAct(int act)
	{
		std::vector<Idea> ideeas;
		for (Idea& i : this->repo.getIdeeas())
		{
			if (i.getStatus() == "accepted" && i.getAct()==act)
				ideeas.push_back(i);
		}
		return ideeas;

	}
};

