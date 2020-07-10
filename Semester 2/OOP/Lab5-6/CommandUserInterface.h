#pragma once
#include <iostream>
#include "CoatService.h"

#define AdministratorMode 2
#define ClientMode 1


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

	void initializeRepository();

	//returns 0 if the user exits the program and 1 if the user changes the mode
	int startAdministratorMode();

	void storeCoat(char** parameters, int numberOfParameters);

	void deleteCoat(char** parameters, int numberOfParameters);

	void updateCoat(char** parameters, int numberOfParameters);

	void listCoats(char** parameters, int numberOfParameters);


	//returns 0 if the user exits the program and 2 if the user changes the mode
	int startClientUserInterface();

	void setIterator();

	void nextCoat(char** parameters, int numberOfParameters);

	void saveTrenchCoatToUserList(char** parameters, int numberOfParameters);

	void listFilteredCoats(char** parameters, int numberOfParameters);

	void listUsersCoats(char** parameters, int numberOfParameters);
};

