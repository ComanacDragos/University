#include "Service.h"

/*
void Service::addHelicopter(int Id, const std::string& model, const std::string& activity, int maxAltitude, const std::string& isPrivate)
{
	Helicopter helicopter{ Id, model, activity, maxAltitude, isPrivate };
	std::unique_ptr<Aircraft> aircraft = std::make_unique<Helicopter>(helicopter);
	this->repo.add(aircraft);
}

void Service::addPlane(int Id, const std::string& model, const std::string& activity, int maxAltitude, const std::string& isPrivate, const std::string& mainWings)
{
	Plane plane{ Id, model, activity, maxAltitude, isPrivate, mainWings };
	std::unique_ptr<Aircraft> aircraft = std::make_unique<Plane>(plane);
	this->repo.add(aircraft);
}

void Service::addBallon(int Id, const std::string& model, const std::string& activity, int maxAltitude, int weightLimit)
{
	HotAirBallon ballon{ Id, model, activity, maxAltitude, weightLimit };
	std::unique_ptr<Aircraft> aircraft = std::make_unique<HotAirBallon>(ballon);
	this->repo.add(aircraft);
}

std::vector<std::unique_ptr<Aircraft>>& Service::getAircraftsActivity(const std::string activity)
{
	std::vector<std::unique_ptr<Aircraft>> aircrafts = this->repo.getAircraftsActivity(activity);
	std::ofstream fout(activity + ".txt");
	for (auto& i : aircrafts)
		fout << i->toString();
	
	return aircrafts;
}

std::vector<std::unique_ptr<Aircraft>>& Service::getAircraftsAltitude(int altitude)
{
	return this->repo.getAircraftsAltitude(altitude);
}
*/