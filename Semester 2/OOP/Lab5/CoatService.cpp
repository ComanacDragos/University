#include "CoatService.h"


CoatService::CoatService(CoatRepository& coatRepository)
{
	this->coatRepository = coatRepository;
}

CoatService::CoatService(const CoatService& coatService)
{
	this->coatRepository = coatService.coatRepository;
	this->userCoats = coatService.userCoats;
	this->coatsIterator = coatService.coatsIterator;
}

CoatService& CoatService::operator=(const CoatService& coatService)
{
	if (this == &coatService)
		return *this;
	this->coatRepository = coatService.coatRepository;
	this->userCoats = coatService.userCoats;
	this->coatsIterator = coatService.coatsIterator;
	return *this;
}

int CoatService::storeCoatService(const std::string& name, const std::string& size, const std::string& photographSource, const std::string& price)
{
	TrenchCoat newCoat{ name, size, photographSource, atoi(price.c_str()) };

	for (int i = 0; i < price.length(); i++)
		if (price[i] < '0' || price[i] > '9')
			return 1;

	int succes = this->coatRepository.storeCoat(newCoat);
	return succes;
}

int CoatService::deleteCoatService(const std::string name)
{
	int succes = this->coatRepository.deleteCoat(name);

	if (succes == 0)
		for (int i = 0; i < this->userCoats.getLength(); i++)
			if (strcmp(this->userCoats.getElement(i).getName().c_str(), name.c_str()) == 0)
			{
				this->userCoats.removeFromPosition(i);
				break;
			}

	return succes;
}

void CoatService::updateCoatService(const std::string& name, const std::string& size, const std::string& photographSource, const std::string& price)
{
	TrenchCoat updatedCoat{ name, size, photographSource, atoi(price.c_str()) };
	this->coatRepository.updateCoat(updatedCoat);

	for (int i = 0; i < this->userCoats.getLength(); i++)
		if (this->userCoats.getElement(i).getName().compare(name.c_str()) == 0)
			this->userCoats.getElement(i) = updatedCoat;

}

DynamicVector<TrenchCoat> CoatService::listCoats()
{
	return this->coatRepository.getAllCoats();
}

void CoatService::openInBrowser(const std::string& name)
{
	TrenchCoat coat = this->coatRepository.findCoatFromRepository(name);
	coat.openInBrowser();
}

TrenchCoat CoatService::getCoatFromRepository(int position)
{
	return this->coatRepository.getCoatFromRepository(position);
}

int CoatService::getRepositoryLenght()
{
	return this->coatRepository.getRepositoryLength();
}


CoatsIterator CoatService::getCoatsIterator()
{
	return CoatsIterator(this->listCoats());
}

void CoatService::saveTrenchCoatToUserList(const std::string& name)
{
	TrenchCoat newUserCoat = this->coatRepository.findCoatFromRepository(name);
	this->userCoats.addElement(newUserCoat);
}

DynamicVector<TrenchCoat> CoatService::listFilteredCoats(const std::string& size, const std::string& price)
{
	DynamicVector<TrenchCoat> filteredCoats;
	
	for (int i = 0; i < this->getRepositoryLenght(); i++)
	{
		TrenchCoat currentCoat = this->getCoatFromRepository(i);

		if (currentCoat.getSize().compare(size) == 0 && currentCoat.getPrice() <= atoi(price.c_str()))
			filteredCoats.addElement(currentCoat);
	}
	return filteredCoats;
}

DynamicVector<TrenchCoat> CoatService::getUserCoats()
{
	return this->userCoats;
}

void CoatService::emptyUserCoats()
{
	DynamicVector<TrenchCoat> emptyList;
	this->userCoats = emptyList;
}

void CoatService::setCoatIteratorToFirst()
{
	this->coatsIterator = this->getCoatsIterator();
}

TrenchCoat CoatService::getNextCoatFromIterator()
{
	TrenchCoat nextCoat = this->coatsIterator.getCurrent();
	this->coatsIterator.next();
	return nextCoat;
}
