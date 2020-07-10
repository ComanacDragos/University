#pragma once
#include "CoatRepository.h"
#include "CoatsIterator.h"

class CoatService
{
private:
	CoatRepository coatRepository;
	DynamicVector <TrenchCoat> userCoats;
	CoatsIterator coatsIterator;

public:
	CoatService(){}

	//copy constructor
	CoatService(CoatRepository& coatRepository);

	CoatService(const CoatService& coatService);

	CoatService& operator=(const CoatService& coatService);

	~CoatService(){}

	//returns 1 if the coat already is in the repository, 0 otherwise
	int storeCoatService(const std::string& name, const std::string& size, const std::string& photographSource, const std::string& price);

	//returns 1 if the coat does not exist in the repository, 0 otherwise
	int deleteCoatService(const std::string name);

	void updateCoatService(const std::string& name, const std::string& size, const std::string& photographSource, const std::string& price);
	
	DynamicVector<TrenchCoat> listCoats();
	
	void openInBrowser(const std::string& name);

	TrenchCoat getCoatFromRepository(int position);

	int getRepositoryLenght();

	//returns an interator over the list of coats
	CoatsIterator getCoatsIterator();

	void saveTrenchCoatToUserList(const std::string& name);

	DynamicVector<TrenchCoat> listFilteredCoats(const std::string& size, const std::string& price);

	DynamicVector<TrenchCoat> getUserCoats();

	void emptyUserCoats();

	void setCoatIteratorToFirst();

	TrenchCoat getNextCoatFromIterator();


};

