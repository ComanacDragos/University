#include "UI.h"

void UI::printMenu()
{
	std::cout << "1.Add helicopter\n";
	std::cout << "2.Add plane\n";
	std::cout << "3.Add balloon\n";
	std::cout << "4.Show model\n";
	std::cout << "5.Show altitude\n";
	std::cout << "6.Exit\n";
	std::cout << "< ";

}

void UI::start()
{
	while (1)
	{
		this->printMenu();
		std::string choice;
		std::getline(std::cin, choice);

		if (choice == "1")
			this->addHelicopter();
		if (choice == "2")
			this->addPlane();
		if (choice == "3")
			this->addBalloon();
		if (choice == "4")
			this->showModels();
		if (choice == "5")
			this->showAltitudes();
		if (choice == "6")
			break;
			
	}

}

void UI::addHelicopter()
{
	std::string id, model, altitude, isPrivate;
	std::cout << "ID: ";
	//std::cin >> id;
	std::getline(std::cin, id);
	std::cout << "Model: ";
	//std::cin >> model;
	std::getline(std::cin, model);
	std::cout << "Altitude: ";
	//std::cin >> altitude;
	std::getline(std::cin, altitude);
	std::cout << "isPrivate: ";
	//std::cin >> isPrivate;
	std::getline(std::cin, isPrivate);
	try
	{
	this->srv.addHelicopter(id, model, altitude, isPrivate);
	std::cout << "Success\n";
	}
	catch (AircraftException & exc)
	{
		std::cout << exc.what();
	}
}

void UI::addPlane()
{

	std::string id, model, altitude, isPrivate, mainWings;
	std::cout << "ID: ";
	//std::cin >> id;
	std::getline(std::cin, id);
	std::cout << "Model: ";
	//std::cin >> model;
	std::getline(std::cin, model);
	std::cout << "Altitude: ";
	//std::cin >> altitude;
	std::getline(std::cin, altitude);
	std::cout << "isPrivate: ";
	//std::cin >> isPrivate;
	std::getline(std::cin, isPrivate);

	std::cout << "mainWings: ";
	//std::cin >> mainWings;
	std::getline(std::cin, mainWings);
	try
	{
		this->srv.addPlane(id, model, altitude, isPrivate, mainWings);
		std::cout << "Success\n";
	}
	catch (AircraftException & exc)
	{
		std::cout << exc.what();
	}
	}

void UI::addBalloon()
{
	std::string id, model, altitude, maxWeight;
	std::cout << "ID: ";
	//std::cin >> id;
	std::getline(std::cin, id);
	std::cout << "Model: ";
	//std::cin >> model;
	std::getline(std::cin, model);
	std::cout << "Altitude: ";
	//std::cin >> altitude;
	std::getline(std::cin, altitude);
	//std::cin >> isPrivate;
	std::cout << "Max weight: ";
	//std::cin >> maxWeight;
	std::getline(std::cin, maxWeight);
	try
	{
		this->srv.addBalloon(id, model, altitude, maxWeight);
		std::cout << "Success\n";
	}
	catch (AircraftException & exc)
	{
		std::cout << exc.what();
	}

}

void UI::showModels()
{
	std::string model;
	std::cout << "Model: ";
	//std::cin >> model;
	std::getline(std::cin, model);
	for (auto& i : this->srv.filterModel(model))
		std::cout << i->toString() << '\n';
}

void UI::showAltitudes()
{

	std::string altitude;
	std::cout << "Altitude: ";
	//std::cin >> altitude;
	std::getline(std::cin, altitude);
	for (auto& i : this->srv.filterAltitude(altitude))
		std::cout << i->toString() << '\n';
}
