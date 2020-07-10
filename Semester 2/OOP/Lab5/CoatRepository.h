#pragma once
#include "DynamicVector.h"
class CoatRepository
{
private:
	DynamicVector<TrenchCoat> coats;

public:
	//default constructor
	CoatRepository(){}

	// copy constructor
	CoatRepository(const CoatRepository& coatRepository);

	CoatRepository& operator=(const CoatRepository& coatRepository);

	~CoatRepository(){}

	//returns 0 if the coat was stored successfuly or 1 if the coat already exists
	int storeCoat(const TrenchCoat& coat);

	////returns 0 if the coat was deleted successfuly or 1 if the coat does not exist
	int deleteCoat(const std::string& name);

	void updateCoat(const TrenchCoat& coat);

	TrenchCoat getCoatFromRepository(int position);

	//returns a coat with a given name
	TrenchCoat findCoatFromRepository(const std::string& name);

	int getRepositoryLength();

	DynamicVector<TrenchCoat> getAllCoats();
};

