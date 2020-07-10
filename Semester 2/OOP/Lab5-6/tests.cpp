#include "tests.h"

void TrenchCoatgetName_TrenchCoat_CorrectName()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };

	assert(coat.getName().compare("name") == 0);
}

void TrenchCoatgetSize_TrenchCoat_CorrectSize()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };

	assert(coat.getSize().compare("size") == 0);
}

void TrenchCoatgetPhotographSource_TrenchCoat_CorrectPhotographSource()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };

	assert(coat.getPhotographSource().compare("photographSource") == 0);
}

void test_TrenchCoat()
{
	TrenchCoatgetName_TrenchCoat_CorrectName();
	TrenchCoatgetSize_TrenchCoat_CorrectSize();
	TrenchCoatgetPhotographSource_TrenchCoat_CorrectPhotographSource();
}

void CoatRepositoryStoreCoat_ValidCoat_ElementAdded()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	CoatRepository repo;

	assert(repo.storeCoat(coat) == 0);
}

void CoatRepositoryStoreCoat_InValidCoat_ElementNotAdded()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	CoatRepository repo;

	repo.storeCoat(coat);
	assert(repo.storeCoat(coat) == 1);
}

void CoatRepositoryDeleteCoat_ValidPosition_ElementDeleted()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	CoatRepository repo;

	repo.storeCoat(coat);
	assert(repo.deleteCoat("name") == 0);
}

void CoatRepositoryDeleteCoat_InvalidPostion_ElementNotDeleted()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	CoatRepository repo;

	repo.storeCoat(coat);
	repo.deleteCoat("name");

	assert(repo.deleteCoat("name") == 1);
}

void CoatRepositoryUpdateCoat_ExistentCoat_UpdatedCoatName()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	TrenchCoat newCoat = { "name", "size2", "photographSource2", 5 };
	CoatRepository repo;
	repo.storeCoat(coat);
	repo.updateCoat(newCoat);

	TrenchCoat updatedCoat = repo.getCoatFromRepository(0);

	assert(updatedCoat.getName().compare("name") == 0);
	}

void CoatRepositoryUpdateCoat_ExistentCoat_UpdatedCoatSize()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	TrenchCoat newCoat = { "name", "size2", "photographSource2", 5 };
	CoatRepository repo;
	repo.storeCoat(coat);
	repo.updateCoat(newCoat);

	TrenchCoat updatedCoat = repo.getCoatFromRepository(0);

	assert(updatedCoat.getSize().compare("size2") == 0);
	}

void CoatRepositoryUpdateCoat_ExistentCoat_UpdatedCoatPhotographSource()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	TrenchCoat newCoat = { "name", "size2", "photographSource2", 5 };
	CoatRepository repo;
	repo.storeCoat(coat);
	repo.updateCoat(newCoat);

	TrenchCoat updatedCoat = repo.getCoatFromRepository(0);

	assert(updatedCoat.getPhotographSource().compare("photographSource2") == 0);
}

void CoatRepositoryUpdateCoat_ExistentCoat_UpdatedCoatPrice()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	TrenchCoat newCoat = { "name", "size2", "photographSource2", 5 };
	CoatRepository repo;
	repo.storeCoat(coat);
	repo.updateCoat(newCoat);

	TrenchCoat updatedCoat = repo.getCoatFromRepository(0);

	assert(updatedCoat.getPrice() == 5);
}

void test_CoatRepository()
{
	CoatRepositoryStoreCoat_ValidCoat_ElementAdded();
	CoatRepositoryStoreCoat_InValidCoat_ElementNotAdded();
	CoatRepositoryDeleteCoat_ValidPosition_ElementDeleted();
	CoatRepositoryDeleteCoat_InvalidPostion_ElementNotDeleted();
	CoatRepositoryUpdateCoat_ExistentCoat_UpdatedCoatName();
	CoatRepositoryUpdateCoat_ExistentCoat_UpdatedCoatPhotographSource();
	CoatRepositoryUpdateCoat_ExistentCoat_UpdatedCoatSize();
	CoatRepositoryUpdateCoat_ExistentCoat_UpdatedCoatPrice();

}

void CoatServiceStoreCoat_ValidCoat_CoatAdded()
{
	CoatRepository repo;
	CoatService service{ repo };
	
	assert(service.storeCoatService("name", "size", "photoSource", "3") == 0);
}

void CoatServiceStoreCoat_InvalidCoat_CoatNotAdded()
{
	CoatRepository repo;
	CoatService service{ repo };

	service.storeCoatService("name", "size", "photoSource", "3");

	assert(service.storeCoatService("name", "size", "photoSource", "3") == 1);
}

void CoatServiceDeleteCoat_ValidCoat_CoatDeleted()
{
	CoatRepository repo;
	CoatService service{ repo };

	service.storeCoatService("name", "size", "photoSource", "3");

	service.storeCoatService("name1", "size", "photoSource", "3");

	assert(service.deleteCoatService("name") == 0 && service.getCoatFromRepository(0) == TrenchCoat("name1", "size", "photoSource", 3));
}

void CoatServiceDeleteCoat_InvalidCoat_CoatNotDeleted()
{
	CoatRepository repo;
	CoatService service{ repo };

	service.storeCoatService("name", "size", "photoSource", "3");

	service.deleteCoatService("name");

	assert(service.deleteCoatService("name") == 1);
}

void CoatServiceUpdateCoat_ValidCoat_UpdatedCoat()
{
	CoatRepository repo;
	CoatService service{ repo };

	service.storeCoatService("name", "size", "photoSource", "3");
	service.updateCoatService("name", "newSize", "newPhotoSource", "5");

	std::vector<TrenchCoat> listOfCoats = service.listCoats();

	TrenchCoat coat = listOfCoats[0];

	assert(coat.to_string().compare("name newSize 5 newPhotoSource") == 0);
}

void CoatServiceSaveTrenchCoatToUserList_ValidCoat_CoatAdded()
{
	CoatRepository repo;
	CoatService service{ repo };
	service.storeCoatService("name", "size", "source", "3");

	service.saveTrenchCoatToUserList("name");

	assert(service.getUserCoats()[0] == TrenchCoat("name", "size", "source", 3));
}

void CoatServiceListFilteredCoats_ThreeCoats_OneCoatAfterFilter()
{
	CoatRepository repo;
	CoatService service{ repo };
	service.storeCoatService("name", "size", "source", "3");
	service.storeCoatService("name1", "size", "source", "5");
	service.storeCoatService("name2", "size2", "source", "3");

	std::vector<TrenchCoat> filtered = service.listFilteredCoats("size", "3");

	assert(filtered[0] == TrenchCoat("name", "size", "source", 3) && filtered.size() == 1);
}

void test_CoatService()
{
	CoatServiceStoreCoat_ValidCoat_CoatAdded();
	CoatServiceStoreCoat_InvalidCoat_CoatNotAdded();
	CoatServiceDeleteCoat_ValidCoat_CoatDeleted();
	CoatServiceDeleteCoat_InvalidCoat_CoatNotDeleted();
	CoatServiceUpdateCoat_ValidCoat_UpdatedCoat();
	CoatServiceSaveTrenchCoatToUserList_ValidCoat_CoatAdded();
	CoatServiceListFilteredCoats_ThreeCoats_OneCoatAfterFilter();
}

void CoatsIteratorGetCurrent_DynamicVectorWithOneElement_CorrectElement()
{
	TrenchCoat coat{ "a","a","a",1 };
	std::vector<TrenchCoat> dynVector;
	dynVector.push_back(coat);

	CoatsIterator iterator{ dynVector };

	assert(iterator.getCurrent() == coat);
}

void CoatsIteratorNext_DynamicVectorWithTwoElements_CorrectSecondElement()
{
	TrenchCoat coat1{ "a","a","a",1 };
	TrenchCoat coat2{ "b","a","a",1 };
	std::vector<TrenchCoat> dynVector;
	dynVector.push_back(coat1);
	dynVector.push_back(coat2);

	CoatsIterator iterator{ dynVector };
	iterator.next();

	assert(iterator.getCurrent() == coat2);
}

void CoatsIteratorNext_DynamicVectorWithTwoElements_LoopsBack()
{
	TrenchCoat coat1{ "a","a","a",1 };
	TrenchCoat coat2{ "b","a","a",1 };
	std:: vector<TrenchCoat> dynVector;
	dynVector.push_back(coat1);
	dynVector.push_back(coat2);

	CoatsIterator iterator{ dynVector };
	iterator.next();
	iterator.next();

	assert(iterator.getCurrent() == coat1);
}

void test_CoatsIterator()
{
	CoatsIteratorGetCurrent_DynamicVectorWithOneElement_CorrectElement();
	CoatsIteratorNext_DynamicVectorWithTwoElements_CorrectSecondElement();
	CoatsIteratorNext_DynamicVectorWithTwoElements_LoopsBack();
}

void testAll()
{
	test_TrenchCoat();
	test_CoatRepository();
	test_CoatService();
	test_CoatsIterator();
	std::cout << "The tests were successful\n";
}