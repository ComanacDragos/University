#pragma once
#include "AbstractRepository.h"
#include "Exceptions.h"

class InMemoryRepository : public AbstractRepository
{
private:
	std::vector<TrenchCoat> coats;

public:
	InMemoryRepository():AbstractRepository() {}

	~InMemoryRepository(){}

	//throws an exception if the coat already exists
	void storeCoat(const TrenchCoat& coat);

	//throws an exception if the coat does not exist
	void deleteCoat(const std::string& name);

	//throws an exception if the coat doesn't exist
	void updateCoat(const TrenchCoat& coat);

	//throws an exception if position is invalid
	TrenchCoat getCoatFromRepository(int position);

	//returns a coat with a given name and throws an exception if there is no such coat
	TrenchCoat findCoatFromRepository(const std::string& name);

	//returns true if the coat exists and false otherwise
	bool existentCoat(const std::string& name);

	int getRepositoryLength();

	std::vector<TrenchCoat> getAllCoats();

	void openFile(){}
};

