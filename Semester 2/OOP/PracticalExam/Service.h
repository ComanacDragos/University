#pragma once
#include "Repository.h"
#include "Observer.h"


class Service : public Observable
{
private:
	Repository& repo;

public:
	Service(Repository& repo) :repo{ repo }{}


	//Creates a star with given name, constelation, coordinates and diameter and adds it to the repository
	//Throws exceptions if the name is empty or if the diameter is less or equal than 0
	void addStar(const std::string& name, const std::string& constelation, int RA, int Dec, int diameter)
	{
		if (name.size() == 0)
			throw Exceptions{ "Name is empty" };
		if (diameter <= 0)
			throw Exceptions{ "Diameter less or equal than 0" };

		this->repo.addStar(Star{ name, constelation, RA, Dec, diameter });
		this->notify();
	}


	Star getStar(const std::string& name)
	{
		return this->repo.getStar(name);
	}

	std::vector<Star> getStarByName(const std::string& name)
	{
		return this->repo.getStarByName(name);
	}
	std::vector<Star> getStars() { return this->repo.getStars(); }
	std::vector<Astronomer> getAstronomers() { return this->repo.getAstronomers(); }
};

