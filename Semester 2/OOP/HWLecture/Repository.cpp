#include "Repository.h"

void Repository::add(std::shared_ptr<Aircraft>& aircraft)
{
	this->aircrafts.push_back(std::move(aircraft));
}

std::vector<std::weak_ptr<Aircraft>> const& Repository::getAircraftsActivity(const std::string activity)
{
	std::vector<std::weak_ptr<Aircraft>> aircrafts;
	for (int i = 0; i < this->aircrafts.size(); i++)
		if (this->aircrafts[i]->getActivity() == activity)
		{
			//std::shared_ptr<Aircraft> aircraft = std::make_shared<Aircraft>(*(this->aircrafts[i]));
			aircrafts.push_back(this->aircrafts[i]);
		}

	return aircrafts;
}

std::vector<std::shared_ptr<Aircraft>> const& Repository::getAircraftsAltitude(int altitude)
{
	std::vector<std::shared_ptr<Aircraft>> aircrafts;
	for (int i = 0; i < this->aircrafts.size(); i++)
		if (this->aircrafts[i]->getAltitude() == altitude)
		{
			//std::unique_ptr<Aircraft> aircraft = std::make_unique<Aircraft>(*(this->aircrafts[i]));
			aircrafts.push_back(this->aircrafts[i]);
		}
	return aircrafts;
}
