#pragma once
#include <string>
#include <string.h>
#include <memory>
#include <exception>

class Aircraft
{
protected:
	std::string id;
	std::string model;
	int maxAltitude;

public:
	Aircraft(const std::string& id, const std::string& model, int maxAltitude):id(id), model(model), maxAltitude(maxAltitude){}

	virtual std::string toString();

	std::string getModel() { return this->model; }

	int getAltitude() { return this->maxAltitude; }

	virtual ~Aircraft(){}
};

class Helicopter : public Aircraft
{
protected:
	std::string isPrivate;

public:
	Helicopter(const std::string& id, const std::string& model, int maxAltitude, const std::string& isPrivate);

	std::string toString() override;

	~Helicopter(){}
};

class Plane : public Aircraft
{
protected:
	std::string isPrivate;
	std::string mainWings;

public:
	Plane(const std::string& id, const std::string& model, int maxAltitude, const std::string& isPrivate, const std::string& mainWings);

	std::string toString() override;

	~Plane(){}
};

class Balloon : public Aircraft
{
protected:
	int maxWeight;

public:
	Balloon(const std::string& id, const std::string& model, int maxAltitude, int maxWeight);

	std::string toString() override;

	~Balloon(){}

};


class AircraftException : public std::exception
{
private:
	std::string message;

public:
	AircraftException(const std::string& message):message(message){}
	std::string what()
	{
		return this->message;
	}
};