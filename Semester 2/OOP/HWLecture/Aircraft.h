#pragma once
#include <string>
#include <string.h>
#include <exception>
#include <iostream>
class Aircraft
{
protected:
	int uniqueIdentifier;
	std::string model;
	std::string activity;
	int maximumAltitude;

public:
	Aircraft(int Id, const std::string& model, const std::string& activity, int maxAltitude);

	virtual std::string toString();

	std::string getActivity();

	int getAltitude();

	virtual ~Aircraft(){}
};

class Helicopter :public Aircraft
{
protected:
	std::string isPrivate;

public:

	Helicopter(int Id, const std::string& model, const std::string& activity, int maxAltitude, const std::string& isPrivate);
	std::string toString();
	~Helicopter(){}
};

class Plane :public Aircraft
{
protected:
	std::string isPrivate;
	std::string mainWings;
public:

	Plane(int Id, const std::string& model, const std::string& activity, int maxAltitude, const std::string& isPrivate, const std::string& mainWings);
	std::string toString();
	~Plane() {}
};

class HotAirBallon : public Aircraft
{
protected:
	int weightLimit;
public:
	HotAirBallon(int Id, const std::string& model, const std::string& activity, int maxAltitude, int weightLimit);
	std::string toString();
	~HotAirBallon() {}
};


class AircraftException :public std::exception
{
private:
	std::string message;

public:
	AircraftException(const std::string& message) :message(message) {}
	std::string what()
	{
		return this->message;
	}
};

