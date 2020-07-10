#pragma once
#include "CoatService.h"

//the maximum lenght of a command
#define CommandLenght 200


//the maximum length in a word in a command
#define WordInCommandLenght 50


class AdministratorUserInterface
{
private:
	CoatService coatService;

public:
	AdministratorUserInterface(){}

	AdministratorUserInterface(const CoatService& coatService);

	AdministratorUserInterface(const AdministratorUserInterface& administratorUserInterface);

	AdministratorUserInterface& operator=(const AdministratorUserInterface& admnistratorUserInterface);

	~AdministratorUserInterface(){}

	//returns 0 if the user exits the program and 1 if the user changes the mode
	int startAdministratorMode();

	void storeCoat(char** parameters, int numberOfParameters);

	void deleteCoat(char** parameters, int numberOfParameters);
	
	void updateCoat(char** parameters, int numberOfParameters);
	
	void listCoats(char** parameters, int numberOfParameters);
};

