#pragma once

#include "Service.h"
#include <sstream>
#include <iostream>
class UI2
{
private:
	Service srv;
public:
	UI2(Service service):srv(service){}

	void start();

	void addHelicopter(std::vector<std::string> parameters);

	void addPlane(std::vector<std::string> parameters);

	void addBalloon(std::vector<std::string> parameters);

	void showModels(std::vector<std::string> parameters);

	void showAltitudes(std::vector<std::string> parameters);

};



