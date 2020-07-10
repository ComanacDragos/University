#include "service.h"
#include <stdlib.h>


Service* createService(Repository* repo)
{
	Service* service = (Service*)malloc(sizeof(Service));
	service->repo = repo;
	return service;
}

void destroyService(Service* service)
{
	destroyRepository(service->repo);
	free(service);

}

void addPlanetService(Service* service, char* name, char* type, double distance)
{
	Planet p = createPlanet(name, type, distance);
	addPlanet(service->repo, p);
	
}
