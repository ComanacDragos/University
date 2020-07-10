#include "Repository.h"

void Repository::add(Aircraft* aircraft)
{
	this->aircrafts.push_back(aircraft);
}

const std::vector<Aircraft*> Repository::getAircrafts()
{
	return this->aircrafts;
}

Repository::~Repository()
{
	for (auto& i : this->aircrafts)
		delete i;
}
