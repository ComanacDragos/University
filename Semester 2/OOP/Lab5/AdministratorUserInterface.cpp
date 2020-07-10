#include "AdministratorUserInterface.h"
#include <string.h>
#include <string>
#include <iostream>

AdministratorUserInterface::AdministratorUserInterface(const CoatService& coatService)
{
	this->coatService = coatService;
}

AdministratorUserInterface::AdministratorUserInterface(const AdministratorUserInterface& administratorUserInterface)
{
	this->coatService = administratorUserInterface.coatService;
}

AdministratorUserInterface& AdministratorUserInterface::operator=(const AdministratorUserInterface& admnistratorUserInterface)
{
	if (this == &admnistratorUserInterface)
		return *this;
	this->coatService = admnistratorUserInterface.coatService;
}

int AdministratorUserInterface::startAdministratorMode()
{

	while (1)
	{
		char userInput[CommandLenght];
		std::cout << "> ";
		
		std::cin.get(userInput, CommandLenght);
		std::cin.get();

		if (strcmp(userInput, "exit") == 0)
			return 0;

		char* splitPointer = strtok(userInput, " ,");

		char** commandParameters = new char* [CommandLenght];

		int i = 0, numberOfParameters;

		while (splitPointer != NULL)
		{
			commandParameters[i] = new char[strlen(splitPointer) + 1];

			strcpy(commandParameters[i], splitPointer);
			splitPointer = strtok(NULL, " ,");
			i++;
		}
		numberOfParameters = i;
		char command[WordInCommandLenght];
		strcpy(command, commandParameters[0]);

		if (strcmp(command, "add") == 0)
			this->storeCoat(commandParameters, numberOfParameters);

		if (strcmp(command, "list") == 0)
			this->listCoats(commandParameters, numberOfParameters);

		if (strcmp(command, "delete") == 0)
			this->deleteCoat(commandParameters, numberOfParameters);

		if (strcmp(command, "update") == 0)
			this->updateCoat(commandParameters, numberOfParameters);


		if (numberOfParameters == 2)
		{	
			char mode[WordInCommandLenght];
			strcpy(mode, commandParameters[1]);
			if (strcmp(command, "mode") == 0 && strcmp(mode, "B") == 0)
				for (i = 0; i < numberOfParameters; i++)
					delete[] commandParameters[i];
				delete[] commandParameters;

				return 1;
	
		}

		for (i = 0; i < numberOfParameters; i++)
			delete[] commandParameters[i];
		delete[] commandParameters;
	}
}

void AdministratorUserInterface::storeCoat(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 5)
	{
		std::cout << "Bad command\n";
		return;
	}
	std::string name = parameters[1];
	std::string size = parameters[2];
	std::string photographSource = parameters[4];
	std::string price = parameters[3];

	if (this->coatService.storeCoatService(name, size, photographSource, price) == 0)
		std::cout << "The coat was added successfuly\n";
	else
		std::cout << "The coat was not added\n";
}

void AdministratorUserInterface::deleteCoat(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 2)
	{
		std::cout << "bad command\n";
		return;
	}
	std::string name = parameters[1];
	
	if (this->coatService.deleteCoatService(name) == 0)
		std::cout << "The coat was successfully deleted\n";
	else
		std::cout << "The coat was not deleted\n";
}

void AdministratorUserInterface::updateCoat(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 5)
	{
		std::cout << "Bad command\n";
		return;
	}
	std::string name = parameters[1];
	std::string size = parameters[2];
	std::string photographSource = parameters[4];
	std::string price = parameters[3];

	this->coatService.updateCoatService(name, size, photographSource, price);

}

void AdministratorUserInterface::listCoats(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 1)
		std::cout << "Bad command\n";
	
	DynamicVector<TrenchCoat> coatList = this->coatService.listCoats();

	for (int i = 0; i < coatList.getLength(); i++)
		std::cout << coatList.getElement(i).to_string() << '\n';
}	

