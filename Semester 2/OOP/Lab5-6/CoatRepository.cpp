#include "CoatRepository.h"


CoatRepository::CoatRepository(const CoatRepository& coatRepository)
{
	this->coats = coatRepository.coats;
}

CoatRepository& CoatRepository::operator=(const CoatRepository& coatRepository)
{
	if (this == &coatRepository)
		return *this;
	this->coats = coatRepository.coats;
	return *this;
}

int CoatRepository::storeCoat(const TrenchCoat& coat)
{
	for (int i = 0; i < this->coats.size(); i++)
		if (this->coats[i] == coat)
			return 1;

	this->coats.push_back(coat);

	return 0;
}

int CoatRepository::deleteCoat(const std::string& name)
{
	for (int i = 0; i < this->coats.size(); i++)
		if (this->coats[i].getName().compare(name) == 0)
		{
			this->coats.erase(this->coats.begin()+i);
			return 0;
		}
	return 1;
}

void CoatRepository::updateCoat(const TrenchCoat& coat)
{
	for (int i = 0; i < this->coats.size(); i++)
		if (this->coats[i].getName().compare(coat.getName()) == 0)
			this->coats[i] = coat;
}

TrenchCoat CoatRepository::getCoatFromRepository(int position)
{
	return this->coats[position];
}

TrenchCoat CoatRepository::findCoatFromRepository(const std::string& name)
{
	for (int i = 0; i < this->getRepositoryLength(); i++)
		if (strcmp(this->coats[i].getName().c_str(), name.c_str()) == 0)
			return this->coats[i];
}

int CoatRepository::getRepositoryLength()
{
	return this->coats.size();
}

std::vector<TrenchCoat> CoatRepository::getAllCoats()
{
	return this->coats;
}
