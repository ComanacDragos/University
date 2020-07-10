#pragma once
#include "TrenchCoat.h"

class AbstractRepository
{
public:
	AbstractRepository(){}

	virtual AbstractRepository& operator=(const AbstractRepository& repo) { return *this; };

	virtual ~AbstractRepository(){}

	//throws an exception if the coat already exists
	virtual void storeCoat(const TrenchCoat& coat) = 0;

	//throws an exception if the coat does not exist
	virtual void deleteCoat(const std::string& name) = 0;

	//throws an exception if the coat doesn't exist
	virtual void updateCoat(const TrenchCoat& coat) = 0;

	//throws an exception if position is invalid
	virtual TrenchCoat getCoatFromRepository(int position) = 0 ;

	//returns a coat with a given name and throws an exception if there is no such coat
	virtual TrenchCoat findCoatFromRepository(const std::string& name) = 0;

	//returns true if the coat exists and false otherwise
	virtual bool existentCoat(const std::string& name) = 0;

	virtual int getRepositoryLength() = 0;

	virtual std::vector<TrenchCoat> getAllCoats() = 0;

	virtual void openFile() = 0;
};

