#pragma once
#include <iostream>
#include "Service.h"

class UI
{
private:
	Service srv;

public:
	UI(Service srv):srv(srv){}

	void printMenu();

	void start();

	void addHelicopter();

	void addPlane();

	void addBalloon();

	void showModels();

	void showAltitudes();

};

