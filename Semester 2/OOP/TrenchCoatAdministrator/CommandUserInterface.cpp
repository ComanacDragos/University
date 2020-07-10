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
	int isRunning = 1;
	std::string filePath, userRepositoryPath;
	while (isRunning)
	{
		std::string userInput;
		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput == "exit")
			return;

		if (userInput.size() == 0)
			continue;

		std::vector <std::string> commandParameters{ tokenize(userInput, ',') };
		int numberOfParameters = commandParameters.size();
		std::string command = commandParameters[0];

		if (command == "fileLocation")
		{

			commandParameters.erase(commandParameters.begin());

			filePath = "";
			for (const std::string& string : commandParameters)
			{
				filePath += string;
				if (*(string.end()-1) != '\\')
					filePath += ' ';
			}
			filePath = filePath.substr(0, filePath.size() - 1);
			std::cout << "File path set successfully\n";
			break;
		}
	}

	isRunning = 1;
	while (isRunning)
	{
		std::string userInput;
		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput == "exit")
			return;

		if (userInput.size() == 0)
			continue;

		std::vector <std::string> commandParameters{ tokenize(userInput, ',') };
		int numberOfParameters = commandParameters.size();
		std::string command = commandParameters[0];

		if (command == "mylistLocation")
		{
			commandParameters.erase(commandParameters.begin());

			userRepositoryPath = "";
			for (const std::string& string : commandParameters)
			{
				userRepositoryPath += string;
				if (*(string.end() - 1) != '\\')
					userRepositoryPath += ' ';
			}
			userRepositoryPath = userRepositoryPath.substr(0, userRepositoryPath.size() - 1);
			std::string fileType = userRepositoryPath.substr(userRepositoryPath.find('.') + 1, std::string::npos);
			
			if (fileType == "html" || fileType == "csv" || fileType == "txt")
			{ 
				std::cout << "mylistLocation set successfully\n";
				break;
			}
		}
	}

	this->coatService.setPath(filePath, userRepositoryPath);

	isRunning = -1; // is -1 until the user chooses a mode
	while (isRunning == -1)
	{
		std::string userInput;
		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput == "exit")
			return;

		if (userInput.size() == 0)
			continue;

		std::vector <std::string> commandParameters{ tokenize(userInput, ',') };
		int numberOfParameters = commandParameters.size();
		std::string command = commandParameters[0];

		if (numberOfParameters == 2)
		{

			if (command == "mode" && commandParameters[1] == "A")
			{
				isRunning = AdministratorMode;
			}

			if (command == "mode" && commandParameters[1] == "B")
			{
				isRunning = ClientMode;
			}
		}
	}

	//this->initializeRepository();

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
	this->coatService.storeCoatService("coat1", "S", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "100");
	this->coatService.storeCoatService("coat2", "M", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "150");
	this->coatService.storeCoatService("coat3", "L", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "120");
	this->coatService.storeCoatService("coat4", "XL", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "130");
	this->coatService.storeCoatService("coat5", "XXL", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "200");
	this->coatService.storeCoatService("coat6", "S", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "130");
	this->coatService.storeCoatService("coat7", "M", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "120");
	this->coatService.storeCoatService("coat8", "L", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "100");
	this->coatService.storeCoatService("coat9", "XL", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "100");
	this->coatService.storeCoatService("coat10", "XXL", "https://m.media-amazon.com/images/I/515R11jmKQL._SR500500_.jpg", "100");
}


int CommandUserInterface::startAdministratorMode()
{
	while (1)
	{
		std::string userInput;
		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput == "exit")
			return ExitCode;

		if (userInput.size() == 0)
			continue;

		std::vector<std::string> commandParameters{ tokenize(userInput, ',') };
		int numberOfParameters = commandParameters.size();
		std::string command = commandParameters[0];

		if (command == "add")
			this->storeCoat(commandParameters, numberOfParameters);

		if (command == "list")
			this->listCoats(commandParameters, numberOfParameters);

		if (command == "delete") 
			this->deleteCoat(commandParameters, numberOfParameters);

		if (command == "update") 
			this->updateCoat(commandParameters, numberOfParameters);

		if (command == "undo")
			this->undo();

		if (command == "redo")
			this->redo();

		if (numberOfParameters == 2)
		{
			std::string mode = commandParameters[1];

			if (command == "mode" && mode == "B")
			{
				return ClientMode;
			}
		}

	}
}

void CommandUserInterface::storeCoat(std::vector<std::string> parameters, int numberOfParameters)
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

	try
	{
		this->coatService.storeCoatService(name, size, photographSource, price);
		std::cout << "The coat was stored succesfully\n";
	}
	catch (Exceptions & exception)
	{
		std::cout << exception.what();
	}
}

void CommandUserInterface::deleteCoat(std::vector<std::string> parameters, int numberOfParameters)
{
	if (numberOfParameters != 2)
	{
		std::cout << "bad command\n";
		return;
	}
	std::string name = parameters[1];

	try
	{
		this->coatService.deleteCoatService(name);
		std::cout << "The coat was deleted succesfully\n";
	}
	catch (Exceptions & exception)
	{
		std::cout << exception.what();
	}
}

void CommandUserInterface::updateCoat(std::vector<std::string> parameters, int numberOfParameters)
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

	try
	{
		this->coatService.updateCoatService(name, size, photographSource, price);
		std::cout << "The coat was updated succesfully\n";
	}
	catch (Exceptions& exception)
	{
		std::cout << exception.what();
	}
}

void CommandUserInterface::listCoats(std::vector<std::string> parameters, int numberOfParameters)
{
	if (numberOfParameters != 1)
		std::cout << "Bad command\n";

	std::vector<TrenchCoat> coatList = this->coatService.listCoats();

	for (TrenchCoat coat:coatList)
		std::cout << coat;
}



int CommandUserInterface::startClientUserInterface()
{
	this->setIterator();
	while (1)
	{
		std::string userInput;
		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput == "exit")
			return ExitCode;

		if (userInput.size() == 0)
			continue;

		std::vector<std::string> commandParameters{ tokenize(userInput, ',') };
		int numberOfParameters = commandParameters.size();
		std::string command = commandParameters[0];
		
		if (command == "next")
			this->nextCoat(commandParameters, numberOfParameters);

		if (command == "save")
			this->saveTrenchCoatToUserList(commandParameters, numberOfParameters);

		if (command == "list")
			this->listFilteredCoats(commandParameters, numberOfParameters);

		if (command == "mylist")
			this->listUsersCoats(commandParameters, numberOfParameters);

		if (numberOfParameters == 2)
		{
			std::string mode = commandParameters[1];
			if (command == "mode" && mode == "A")
			{
				return AdministratorMode;
			}
		}
	}
}

void CommandUserInterface::setIterator()
{
	this->coatService.setCoatIteratorToFirst();
}

void CommandUserInterface::nextCoat(std::vector<std::string> parameters, int numberOfParameters)
{
	if (numberOfParameters != 1)
	{
		std::cout << "Bad command\n";
		return;
	}

	std::cout << this->coatService.getNextCoatFromIterator();
}

void CommandUserInterface::saveTrenchCoatToUserList(std::vector<std::string> parameters, int numberOfParameters)
{
	if (numberOfParameters != 2)
	{
		std::cout << "Bad command\n";
		return;
	}
	std::string name = parameters[1];
	try
	{
		this->coatService.saveTrenchCoatToUserList(name);
		std::cout << "The coat was added to shopping basket\n";
	}
	catch (Exceptions & exception)
	{
		std::cout << exception.what();
	}
	
}

void CommandUserInterface::listFilteredCoats(std::vector<std::string> parameters, int numberOfParameters)
{
	if (numberOfParameters != 3)
	{
		std::cout << "Bad command\n";
		return;
	}
	std::string size = parameters[1];
	std::string price = parameters[2];
	std::vector<TrenchCoat> filteredCoats = this->coatService.listFilteredCoats(size, price);

	for (TrenchCoat coat : filteredCoats)
		std::cout << coat;
}

void CommandUserInterface::listUsersCoats(std::vector<std::string> parameters, int numberOfParameters)
{
	if (numberOfParameters != 1)
	{
		std::cout << "Bad command\n";
	}
	
	/*
	std:: vector<TrenchCoat> userCoats = this->coatService.getUserCoats();
	
	for (TrenchCoat coat : userCoats)
		std::cout << coat;
	*/
	this->coatService.openUserFile();
}

void CommandUserInterface::undo()
{
	try
	{
		this->coatService.undo();
		std::cout << "Successful undo\n";
	}
	catch(UndoException exc)
	{
		std::cout << exc.what();
	}
}

void CommandUserInterface::redo()
{
	try
	{
		this->coatService.redo();
		std::cout << "Successful redo\n";
	}
	catch (UndoException exc)
	{
		std::cout << exc.what();
	}
}
