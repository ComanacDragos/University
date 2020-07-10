#pragma once
#include <iostream>
#include <sstream>
#include "CoatService.h"

#define AdministratorMode 2
#define ClientMode 1
#define ExitCode 0

//the maximum lenght of a command
#define CommandLenght 200


//the maximum length in a word in a command
#define WordInCommandLenght 50

class CommandUserInterface
{
private:
	CoatService coatService;

public:
	CommandUserInterface(){}

	CommandUserInterface(const CoatService& coatService);

	CommandUserInterface(const CommandUserInterface& commandUserInterface);

	CommandUserInterface& operator=(const CommandUserInterface& commandUserInterface);

	~CommandUserInterface(){}

	void startProgram();

private:
	void initializeRepository();

	//returns 0 if the user exits the program and 1 if the user changes the mode
	int startAdministratorMode();

	void storeCoat(std::vector<std::string> parameters, int numberOfParameters);

	void deleteCoat(std::vector<std::string> parameters, int numberOfParameters);

	void updateCoat(std::vector<std::string> parameters, int numberOfParameters);

	void listCoats(std::vector<std::string> parameters, int numberOfParameters);


	//returns 0 if the user exits the program and 2 if the user changes the mode
	int startClientUserInterface();

	void setIterator();

	void nextCoat(std::vector<std::string> parameters, int numberOfParameters);

	void saveTrenchCoatToUserList(std::vector<std::string> parameters, int numberOfParameters);

	void listFilteredCoats(std::vector<std::string> parameters, int numberOfParameters);

	void listUsersCoats(std::vector<std::string> parameters, int numberOfParameters);

	void undo();

	void redo();
};

