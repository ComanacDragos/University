#include "Aircraft.h"

Aircraft::Aircraft(int Id, const std::string& model, const std::string& activity, int maxAltitude)
{
	this->uniqueIdentifier = Id;
	this->model = model;
	this->activity = activity;
	this->maximumAltitude = maxAltitude;
}

std::string Aircraft::toString()
{
	return std::to_string(this->uniqueIdentifier) + " " + this->model + " " + this->activity + " " + std::to_string(this->maximumAltitude);
}

std::string Aircraft::getActivity()
{
	return this->activity;
}

int Aircraft::getAltitude()
{
	return this->maximumAltitude;
}

Helicopter::Helicopter(int Id, const std::string& model, const std::string& activity, int maxAltitude, const std::string& isPrivate):Aircraft{Id, model,activity, maxAltitude}
{
	if (activity == "leisure time" && isPrivate != "private")
		throw AircraftException("Aircraft not private\n");

	if (maxAltitude > 12)
		throw AircraftException("Aircraft altitude too high");
	this->isPrivate = isPrivate;
}

std::string Helicopter::toString()
{
	return Aircraft::toString() + " " + this->isPrivate;
}

Plane::Plane(int Id, const std::string& model, const std::string& activity, int maxAltitude, const std::string& isPrivate, const std::string& mainWings):Aircraft{Id, model, activity, maxAltitude}
{
	if (activity == "leisure time" && mainWings != "biplane")
		throw AircraftException("Aircraft not suitable for leisure time\n");
	if(maxAltitude > 26)
		throw AircraftException("Aircraft altitude too high");

	this->isPrivate = isPrivate;
	this->mainWings = mainWings;
}

std::string Plane::toString()
{
	return Aircraft::toString() + " " + this->isPrivate + " " + this->mainWings;
}

HotAirBallon::HotAirBallon(int Id, const std::string& model, const std::string& activity, int maxAltitude, int weightLimit) :Aircraft{ Id, model, activity, maxAltitude }
{
	if (activity != "leisure time")
		throw AircraftException("Not leisure time\n");
	if (maxAltitude > 21)
		throw AircraftException("Aircraft altitude too high");

	this->weightLimit = weightLimit;
}

std::string HotAirBallon::toString()
{
	return Aircraft::toString() + " " + std::to_string(this->weightLimit);
}


std::ostream& operator<<(std::ostream& ostream, Aircraft& aircraft)
{
	ostream << aircraft.toString() << '\n';
	return ostream;

}