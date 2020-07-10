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

void DynamicVectoraddElement_ValidElement_ElementAdded()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	DynamicVector<TrenchCoat> dynVector;
	dynVector.addElement(coat);

	assert(dynVector.getLength() == 1);
}

void DynamicVectorremoveElement_ValidPosition_ElementRemoved()
{
	TrenchCoat coat = { "name", "size", "photographSource", 4 };
	DynamicVector<TrenchCoat> dynVector;
	dynVector.addElement(coat);
	dynVector.addElement(TrenchCoat("name1", "size", "source", 3));
	dynVector.removeFromPosition(0);

	assert(dynVector.getLength() == 1);
}

void DynamicVectorIncreaseSize_DynamicVector_LargerDynamicVector()
{
	DynamicVector<TrenchCoat> dynVector;
	TrenchCoat coat1{ "n1", "s", "s", 4 };
	TrenchCoat coat2{ "n2", "s", "s", 4 };
	TrenchCoat coat3{ "n3", "s", "s", 4 };
	dynVector.addElement(coat1);
	dynVector.addElement(coat2);
	dynVector.addElement(coat3);

	assert(dynVector.getLength() == 3);
}

void DynamicVectorIncreaseSize_DynamicVector_SmallerDynamicVector()
{
	DynamicVector<TrenchCoat> dynVector;
	TrenchCoat coat1{ "n1", "s", "s", 4 };
	TrenchCoat coat2{ "n2", "s", "s", 4 };
	TrenchCoat coat3{ "n3", "s", "s", 4 };
	dynVector.addElement(coat1);
	dynVector.addElement(coat2);
	dynVector.addElement(coat3);
	dynVector.removeFromPosition(1);

	assert(dynVector.getLength() == 2);
}

void test_DynamicVector()
{
	DynamicVectoraddElement_ValidElement_ElementAdded();
	DynamicVectorremoveElement_ValidPosition_ElementRemoved();
	DynamicVectorIncreaseSize_DynamicVector_LargerDynamicVector();
	DynamicVectorIncreaseSize_DynamicVector_SmallerDynamicVector();
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

	DynamicVector<TrenchCoat> listOfCoats = service.listCoats();

	TrenchCoat coat = listOfCoats.getElement(0);

	assert(coat.to_string().compare("name newSize 5 newPhotoSource") == 0);
}

void CoatServiceSaveTrenchCoatToUserList_ValidCoat_CoatAdded()
{
	CoatRepository repo;
	CoatService service{ repo };
	service.storeCoatService("name", "size", "source", "3");

	service.saveTrenchCoatToUserList("name");
	assert(service.getUserCoats().getElement(0) == TrenchCoat("name", "size", "source", 3));
}

void CoatServiceListFilteredCoats_ThreeCoats_OneCoatAfterFilter()
{
	CoatRepository repo;
	CoatService service{ repo };
	service.storeCoatService("name", "size", "source", "3");
	service.storeCoatService("name1", "size", "source", "5");
	service.storeCoatService("name2", "size2", "source", "3");

	DynamicVector<TrenchCoat> filtered = service.listFilteredCoats("size", "3");

	assert(filtered.getElement(0) == TrenchCoat("name", "size", "source", 3) && filtered.getLength() == 1);
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
	DynamicVector<TrenchCoat> dynVector;
	dynVector.addElement(coat);

	CoatsIterator iterator{ dynVector };

	assert(iterator.getCurrent() == coat);
}

void CoatsIteratorNext_DynamicVectorWithTwoElements_CorrectSecondElement()
{
	TrenchCoat coat1{ "a","a","a",1 };
	TrenchCoat coat2{ "b","a","a",1 };
	DynamicVector<TrenchCoat> dynVector;
	dynVector.addElement(coat1);
	dynVector.addElement(coat2);

	CoatsIterator iterator{ dynVector };
	iterator.next();

	assert(iterator.getCurrent() == coat2);
}

void CoatsIteratorNext_DynamicVectorWithTwoElements_LoopsBack()
{
	TrenchCoat coat1{ "a","a","a",1 };
	TrenchCoat coat2{ "b","a","a",1 };
	DynamicVector<TrenchCoat> dynVector;
	dynVector.addElement(coat1);
	dynVector.addElement(coat2);

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
	test_DynamicVector();
	test_CoatRepository();
	test_CoatService();
	test_CoatsIterator();
	std::cout << "The tests were successful\n";
}