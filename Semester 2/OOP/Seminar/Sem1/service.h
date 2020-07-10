#pragma once
#include "Repository.h"
#include <stdlib.h>

typedef struct 
{
	Repository* repo;

}Service;

Service* createService(Repository* repo);
void destroyService(Service* service);

void addPlanetService(Service* service, char* name, char* type, double distance);
