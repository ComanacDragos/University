#include "Aircraft.h"

std::string Aircraft::toString()
{
	return this->id + " " + this->model + " " + std::to_string(this->maxAltitude);
}

Helicopter::Helicopter(const std::string& id, const std::string& model, int maxAltitude, const std::string& isPrivate) :Aircraft(id, model, maxAltitude), isPrivate(isPrivate)
{
	
}

std::string Helicopter::toString()
{
	return Aircraft::toString() + " " + this->isPrivate;
}

Plane::Plane(const std::string& id, const std::string& model, int maxAltitude, const std::string& isPrivate, const std::string& mainWings) :Aircraft(id, model, maxAltitude), isPrivate(isPrivate), mainWings(mainWings)
{
}

std::string Plane::toString()
{
	return Aircraft::toString() + " " + this->isPrivate + " " + this->mainWings;
}

Balloon::Balloon(const std::string& id, const std::string& model, int maxAltitude, int maxWeight) :Aircraft(id, model, maxAltitude), maxWeight(maxWeight)
{
}

std::string Balloon::toString()
{
	return Aircraft::toString() + " " + std::to_string(this->maxWeight);
}
