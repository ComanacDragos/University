#include "ClientUserInterface.h"

ClientUserInterface::ClientUserInterface(const CoatService& coatService)
{
	this->coatService = coatService;
}

ClientUserInterface::ClientUserInterface(const ClientUserInterface& clientUserInterface)
{
	this->coatService = clientUserInterface.coatService;
	this->coatsIterator = clientUserInterface.coatsIterator;
}

ClientUserInterface& ClientUserInterface::operator=(const ClientUserInterface& clientUserInterface)
{
	if (this == &clientUserInterface)
		return *this;
	this->coatService = clientUserInterface.coatService;
	this->coatsIterator = clientUserInterface.coatsIterator;
	return *this;
}

int ClientUserInterface::startClientUserInterface()
{
	this->setIterator();
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

		if (numberOfParameters == 2)
		{
			char mode[WordInCommandLenght];
			strcpy(mode, commandParameters[1]);
			if (strcmp(command, "mode") == 0 && strcmp(mode, "A") == 0)

				for (i = 0; i < numberOfParameters; i++)
					delete[] commandParameters[i];
				delete[] commandParameters;
				
				return 2;
		}

		if (strcmp(command, "next") == 0)
			this->nextCoat(commandParameters, numberOfParameters);

		for (i = 0; i < numberOfParameters; i++)
			delete[] commandParameters[i];
		delete[] commandParameters;
	}
}

void ClientUserInterface::setIterator()
{
	this->coatsIterator = this->coatService.coatsIterator();
}

void ClientUserInterface::nextCoat(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 1)
	{
		std::cout << "Bad command\n";
		return;
	}

	DynamicVector<TrenchCoat> coatList = this->coatService.listCoats();

	for (int i = 0; i < coatList.getLength(); i++)
		std::cout << coatList.getElement(i).to_string() << '\n';
	//std::cout << this->coatsIterator.getCurrent().to_string()<<'\n';
	//this->coatsIterator.next();
}



