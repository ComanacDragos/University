#include "CommandUserInterface.h"

CommandUserInterface::CommandUserInterface(const CoatService& coatService)
{
	this->coatService = coatService;

	//this->initializeRepository();
}

CommandUserInterface::CommandUserInterface(const CommandUserInterface& commandUserInterface)
{
	this->coatService = commandUserInterface.coatService;
}

CommandUserInterface& CommandUserInterface::operator=(const CommandUserInterface& commandUserInterface)
{
	if (this == &commandUserInterface)
		return *this;
	this->coatService = commandUserInterface.coatService;
	return *this;
}

void CommandUserInterface::startProgram()
{
	int isRunning = -1; // is -1 until the user chooses a mode
	while (isRunning == -1)
	{
		char userInput[CommandLenght];
		std::cout << "> ";

		std::cin.get(userInput, CommandLenght);
		std::cin.get();

		if (strcmp(userInput, "exit") == 0)
			break;

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
			
			if(strcmp(command, "mode") == 0 && strcmp(commandParameters[1], "A") == 0)
			{
				isRunning = AdministratorMode;
			}

			if (strcmp(command, "mode") == 0 && strcmp(commandParameters[1], "B") == 0)
			{
				isRunning = ClientMode;
			}
		}

		for (i = 0; i < numberOfParameters; i++)
			delete[] commandParameters[i];
		delete[] commandParameters;
	}

	while (isRunning == AdministratorMode || isRunning == ClientMode)
	{
		if (isRunning == AdministratorMode)
		{
			isRunning = this->startAdministratorMode();
		}

		if (isRunning == ClientMode)
		{
			isRunning = this->startClientUserInterface();
		}
	}
}

void CommandUserInterface::initializeRepository()
{
	this->coatService.storeCoatService("coat1", "S", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "100");
	this->coatService.storeCoatService("coat2", "M", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "150");
	this->coatService.storeCoatService("coat3", "L", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "120");
	this->coatService.storeCoatService("coat4", "XL", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "130");
	this->coatService.storeCoatService("coat5", "XXL", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "200");
	this->coatService.storeCoatService("coat6", "S", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "130");
	this->coatService.storeCoatService("coat7", "M", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "120");
	this->coatService.storeCoatService("coat8", "L", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "100");
	this->coatService.storeCoatService("coat9", "XL", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "100");
	this->coatService.storeCoatService("coat10", "XXL", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500,500_.jpg", "100");
}


int CommandUserInterface::startAdministratorMode()
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
			{
				for (i = 0; i < numberOfParameters; i++)
					delete[] commandParameters[i];
				delete[] commandParameters;

				return ClientMode;
			}
		}

		for (i = 0; i < numberOfParameters; i++)
			delete[] commandParameters[i];
		delete[] commandParameters;
	}
}

void CommandUserInterface::storeCoat(char** parameters, int numberOfParameters)
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

void CommandUserInterface::deleteCoat(char** parameters, int numberOfParameters)
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

void CommandUserInterface::updateCoat(char** parameters, int numberOfParameters)
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

void CommandUserInterface::listCoats(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 1)
		std::cout << "Bad command\n";

	DynamicVector<TrenchCoat> coatList = this->coatService.listCoats();

	for (int i = 0; i < coatList.getLength(); i++)
		std::cout << coatList.getElement(i).to_string() << '\n';
}



int CommandUserInterface::startClientUserInterface()
{
	this->setIterator();
	//this->coatService.emptyUserCoats();
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


		if (strcmp(command, "next") == 0)
			this->nextCoat(commandParameters, numberOfParameters);

		if (strcmp(command, "save") == 0)
			this->saveTrenchCoatToUserList(commandParameters, numberOfParameters);

		if (strcmp(command, "list") == 0)
			this->listFilteredCoats(commandParameters, numberOfParameters);

		if (strcmp(command, "mylist") == 0)
			this->listUsersCoats(commandParameters, numberOfParameters);

		if (numberOfParameters == 2)
		{
			char mode[WordInCommandLenght];
			strcpy(mode, commandParameters[1]);
			if (strcmp(command, "mode") == 0 && strcmp(mode, "A") == 0)
			{
				for (i = 0; i < numberOfParameters; i++)
					delete[] commandParameters[i];
				delete[] commandParameters;

				return AdministratorMode;
			}
		}

		for (i = 0; i < numberOfParameters; i++)
			delete[] commandParameters[i];
		delete[] commandParameters;
	}
}

void CommandUserInterface::setIterator()
{
	this->coatService.setCoatIteratorToFirst();
}

void CommandUserInterface::nextCoat(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 1)
	{
		std::cout << "Bad command\n";
		return;
	}

	//DynamicVector<TrenchCoat> coatList = this->coatService.listCoats();

	//std::cout << this->coatsIterator.getCurrent().to_string()<<'\n';
	//this->coatsIterator.next();
	std::cout << this->coatService.getNextCoatFromIterator().to_string() << '\n';
}

void CommandUserInterface::saveTrenchCoatToUserList(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 2)
	{
		std::cout << "Bad command\n";
		return;
	}
	std::string name = parameters[1];
	this->coatService.saveTrenchCoatToUserList(name);
	std::cout << "The coat was added to shopping basket\n";
}

void CommandUserInterface::listFilteredCoats(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 3)
	{
		std::cout << "Bad command\n";
		return;
	}
	std::string size = parameters[1];
	std::string price = parameters[2];
	DynamicVector<TrenchCoat> filteredCoats = this->coatService.listFilteredCoats(size, price);

	for (int i = 0; i < filteredCoats.getLength(); i++)
		std::cout << filteredCoats.getElement(i).to_string() << '\n';
}

void CommandUserInterface::listUsersCoats(char** parameters, int numberOfParameters)
{
	if (numberOfParameters != 1)
	{
		std::cout << "Bad command\n";
	}
	DynamicVector<TrenchCoat> userCoats = this->coatService.getUserCoats();
	
	for (int i = 0; i < userCoats.getLength(); i++)
		std::cout << userCoats.getElement(i).to_string() << '\n';
}
