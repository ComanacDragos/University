#pragma once

#include "Planet.h"
#define MAX_DIM 100

typedef struct
{
	Planet elems[MAX_DIM];
	int lenght;

}Repository;

Repository* createRepository();
void destroyRepository(Repository* repo); // enough to specify types

/*
Searches for a planet in the repository(by planet name)
Input: repo - pointer to repository
	   p - planet
Output: 1 - if planet was found
		0 - otherwise
*/
int findPlanetRepository(Repository* repo, Planet p);


/*
Adds a planet to the repository.
Input: repo - pointer to repository
	   p - planet
Output: 1 if planet was not added (already exists)
		0 otherwise
*/
int addPlanet(Repository* repo, Planet p);

void testRepository();