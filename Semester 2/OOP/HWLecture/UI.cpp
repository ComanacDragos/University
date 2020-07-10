#include "UI.h"
/*
void UI::startProgram()
{
	while (1)
	{
		std::cout << "1.Add helicopter\n2.Add plane\n3.Add ballon\n4.Show planes by activity\n5.Show planes by max altitude\n";
	}
}

void UI::readHelicopter()
{
	std::string Id;
	std::string model;
	std::string activity;
	std::string maxAltitude;
	std::string isPrivate;
	std::cout << "Id: ";
	std::getline(std::cin, Id);
	std::cout << "Model: ";
	std::getline(std::cin, model);
	std::cout << "Activity: ";
	std::getline(std::cin, activity);
	std::cout << "MaxAltitude: ";
	std::getline(std::cin, maxAltitude);
	std::cout << "IsPrivate: ";
	std::getline(std::cin, isPrivate);

	try
	{
		this->srv.addHelicopter(std::stoi(Id), model, activity, std::stoi(maxAltitude), isPrivate);
	}
	catch (AircraftException excp)
	{
		std::cout << excp.what();
	}

}

void UI::readPlane()
{
}

void UI::readBaloon()
{
}
*/