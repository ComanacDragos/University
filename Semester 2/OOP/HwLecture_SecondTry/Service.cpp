#include "Service.h"

void Service::addHelicopter(const std::string& id, const std::string& model, const std::string& maxAltitude, const std::string& isPrivate)
{
	std::string exceptions;
	if (model == "leisure time" && isPrivate != "private")
		exceptions += "Not private\n";
	if (stoi(maxAltitude) > 12)
		exceptions += "Altitude must be less than 12\n";
	if (exceptions.size() != 0)
		throw(AircraftException(exceptions));

	Aircraft* aircraft = new Helicopter{ id, model, stoi(maxAltitude), isPrivate };
	this->repo.add(aircraft);
}

void Service::addPlane(const std::string& id, const std::string& model, const std::string& maxAltitude, const std::string& isPrivate, const std::string& mainWings)
{
	std::string exceptions;
	if (model == "leisure time" && mainWings != "biplane")
		exceptions += "Not biplane\n";
	if (stoi(maxAltitude) > 26)
		exceptions += "Altitude must be less than 26\n";
	if (exceptions.size() != 0)
		throw(AircraftException(exceptions));

	Aircraft* aircraft = new Plane{ id, model, stoi(maxAltitude), isPrivate, mainWings };
	this->repo.add(aircraft);

}

void Service::addBalloon(const std::string& id, const std::string& model, const std::string& maxAltitude, const std::string& maxWeight)
{
	std::string exceptions;
	if (model != "leisure time")
		exceptions += "Not leisure\n";
	if (stoi(maxAltitude) > 21)
		exceptions += "Altitude must be less than 21\n";
	if (exceptions.size() != 0)
		throw(AircraftException(exceptions));

	Aircraft* aircraft = new Balloon{ id, model, stoi(maxAltitude), stoi(maxWeight) };
	this->repo.add(aircraft);
}

const std::vector<Aircraft*> Service::filterModel(std::string model)
{
	std::vector<Aircraft*> filteredAircrafts;

	for (auto& aircraft : this->repo.getAircrafts())
		if (aircraft->getModel() == model)
			filteredAircrafts.push_back(aircraft);
	
	if (filteredAircrafts.size() != 0)
	{
		std::ofstream fileOut{ model + ".txt" };
		for (auto& aircraft : filteredAircrafts)
			fileOut << aircraft->toString() << '\n';
	}
	return filteredAircrafts;
}

const std::vector<Aircraft*> Service::filterAltitude(std::string altitude)
{
	std::vector<Aircraft*> filteredAircrafts;

	for (auto& aircraft : this->repo.getAircrafts())
		if (aircraft->getAltitude() <= stoi(altitude))
			filteredAircrafts.push_back(aircraft);

	return filteredAircrafts;
}
