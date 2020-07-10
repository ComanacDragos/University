#include "Repository.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef Planet TElem;

Repository* createRepository()
{
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (repo == NULL)
		return NULL;
	repo->lenght = 0;
	return repo;
}

void destroyRepository(Repository* repo)
{
	free(repo);
}

int findPlanetRepository(Repository* repo, TElem p)
{
	for (int i=0;i<repo->lenght;i++)
		if (strcmp(getName(&repo->elems[i]), getName(&p)) == 0)
			return 1;
		return 0;

	return 0;
}

int addPlanet(Repository* repo, TElem p)
{
	if (findPlanetRepository(repo, p) == 0)
	{
		repo->elems[repo->lenght++] = p;
		return 0;
	}
	return 1;

}

void testRepository()
{
	Repository* repo = createRepository();
	Planet p = createPlanet("earth", "terra", 0);
	assert (addPlanet(repo, p) == 0);
	assert(addPlanet(repo, p) == 1);
	//destroyRepository(repo);
}
