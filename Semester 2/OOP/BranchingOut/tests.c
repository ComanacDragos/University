#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "tests.h"
#include "domain.h"
#include "repository.h"
#include "service.h"


void getCatalogueNumber_catalogueNumber_CorrectCatalogueNumber()
{
	Product product = createProduct(123, "abc", "def", 456);
	assert(getCatalogueNumber(&product) == 123);
}
void getValue_value_CorrectValue()
{
	Product product = createProduct(123, "abc", "def", 456);
	assert(getValue(&product) == 456);
}
void getState_state_CorrectState()
{
	Product product = createProduct(123, "abc", "def", 456);
	assert(strcmp(getState(&product), "abc") == 0);
}
void getType_type_CorrectType()
{
	Product product = createProduct(123, "abc", "def", 456);
	assert(strcmp(getType(&product), "def") == 0);
}
void updateState_newState_StateUpdated()
{
	Product product = createProduct(123, "abc", "def", 456);
	updateState(&product, "newState");
	assert(strcmp(getState(&product), "newState") == 0);

}
void updateType_newType_TypeUpdated()
{
	Product product = createProduct(123, "abc", "def", 456);
	updateType(&product, "newType");
	assert(strcmp(getType(&product), "newType") == 0);

}
void updateValue_newValue_ValueUpdated()
{
	Product product = createProduct(123, "abc", "def", 456);
	updateValue(&product, 999);
	assert(getValue(&product) == 999);

}
void testProduct()
{
	getCatalogueNumber_catalogueNumber_CorrectCatalogueNumber();
	getValue_value_CorrectValue();
	getState_state_CorrectState();
	getType_type_CorrectType();

	updateState_newState_StateUpdated();
	updateType_newType_TypeUpdated();
	updateValue_newValue_ValueUpdated();
}


void storeProduct_validProduct_addedToList()
{
	ProductRepository* productRepo = createProductRepository();
	Product product = createProduct(123, "abc", "def", 456);

	assert(storeProduct(productRepo, product) == 0);
	destroyRepository(productRepo);
}

void storeProduct_InvalidProduct_ReturnsErrorCode1()
{
	ProductRepository* productRepo = createProductRepository();
	Product product = createProduct(123, "abc", "def", 456);
	
	storeProduct(productRepo, product);
	assert(storeProduct(productRepo, product) == 1);
	destroyRepository(productRepo);
}

void removeProduct_ValidProduct_removedProduct()
{
	ProductRepository* productRepo = createProductRepository();
	Product product = createProduct(123, "abc", "def", 456);
	storeProduct(productRepo, product);
	
	assert(removeProduct(productRepo, 123) == 0);
	destroyRepository(productRepo);
}
void removeProduct_InvalidProduct_ReturnsErrorCode1()
{
	ProductRepository* productRepo = createProductRepository();
	
	assert(removeProduct(productRepo, 123) == 1);
	destroyRepository(productRepo);
}
void findProduct_ValidProduct_ReturnsIndex0()
{
	ProductRepository* productRepo = createProductRepository();
	Product product = createProduct(123, "abc", "def", 456);
	storeProduct(productRepo, product);

	assert(findProduct(productRepo, 123) == 0);
	destroyRepository(productRepo);
}
void findProduct_InexistentProduct_ReturnsNegative()
{
	ProductRepository* productRepo = createProductRepository();

	assert(findProduct(productRepo, 123) == -1);
	destroyRepository(productRepo);
}
void getProduct_ExistentProduct_AddressOfTheProduct()
{
	ProductRepository* productRepo = createProductRepository();
	Product product = createProduct(123, "abc", "def", 456);
	storeProduct(productRepo, product);
	Product* productFromRepo = &productRepo->products[0];
	
	assert(productFromRepo == getProduct(productRepo, 0));
	destroyRepository(productRepo);
}
void getProduct_InvalidIndex_ReturnsNULL()
{
	ProductRepository* productRepo = createProductRepository();
	Product* productFromRepo = getProduct(productRepo, 1);

	assert(productFromRepo == NULL);
	destroyRepository(productRepo);
}
void updateProduct_ValidProduct_UpdatedState()
{
	ProductRepository* productRepo = createProductRepository();
	Product product = createProduct(123, "abc", "def", 456);
	storeProduct(productRepo, product);
	updateProduct(productRepo, 123, "newState", "def", 456);

	assert(strcmp(getState(getProduct(productRepo, 0)),"newState") == 0);
	destroyRepository(productRepo);
}
void updateProduct_ValidProduct_UpdatedType()
{
	ProductRepository* productRepo = createProductRepository();
	Product product = createProduct(123, "abc", "def", 456);
	storeProduct(productRepo, product);
	updateProduct(productRepo, 123, "abc", "newType", 456);

	assert(strcmp(getType(getProduct(productRepo, 0)), "newType") == 0);
	destroyRepository(productRepo);
}
void updateProduct_ValidProduct_UpdatedValue()
{
	ProductRepository* productRepo = createProductRepository();
	Product product = createProduct(123, "abc", "def", 456);
	storeProduct(productRepo, product);
	updateProduct(productRepo, 123, "abc", "def", 123);

	assert(getValue(getProduct(productRepo, 0)) == 123);
	destroyRepository(productRepo);
}
void repositoryLength_RepositoryWithTwoProducts()
{
	ProductRepository* productRepo = createProductRepository();
	storeProduct(productRepo, createProduct(123, "abc", "def", 456));
	storeProduct(productRepo, createProduct(124, "abc", "def", 456));

	assert(repositoryLength(productRepo) == 2);
	destroyRepository(productRepo);
}
void increaseRepositorySize_EmptyRepositoryWithcapacity2_RepositoryWith3ElementsCapacity4()
{
	ProductRepository* productRepo = createProductRepository();
	storeProduct(productRepo, createProduct(123, "abc", "def", 456));
	storeProduct(productRepo, createProduct(124, "abc", "def", 456));
	storeProduct(productRepo, createProduct(125, "abc", "def", 456));

	assert(productRepo->capacity == 4);
	destroyRepository(productRepo);
}
void shrinkRepository_RepositoryCapacity4_RepositoryCapacity2()
{
	ProductRepository* productRepo = createProductRepository();
	storeProduct(productRepo, createProduct(123, "abc", "def", 456));
	storeProduct(productRepo, createProduct(124, "abc", "def", 456));
	storeProduct(productRepo, createProduct(125, "abc", "def", 456));
	removeProduct(productRepo, 123);

	assert(productRepo->capacity == 2);
	destroyRepository(productRepo);
}

void testRepository()
{
	storeProduct_validProduct_addedToList();
	storeProduct_InvalidProduct_ReturnsErrorCode1();
	removeProduct_ValidProduct_removedProduct();
	removeProduct_InvalidProduct_ReturnsErrorCode1();
	findProduct_ValidProduct_ReturnsIndex0();
	findProduct_InexistentProduct_ReturnsNegative();
	getProduct_ExistentProduct_AddressOfTheProduct();
	getProduct_InvalidIndex_ReturnsNULL();
	updateProduct_ValidProduct_UpdatedState();
	updateProduct_ValidProduct_UpdatedType();
	updateProduct_ValidProduct_UpdatedValue();
	repositoryLength_RepositoryWithTwoProducts();
	increaseRepositorySize_EmptyRepositoryWithcapacity2_RepositoryWith3ElementsCapacity4();
	shrinkRepository_RepositoryCapacity4_RepositoryCapacity2();
}

void storeProductService_ValidProduct_StoredProduct()
{
	ProductRepository* repo = createProductRepository();
	ProductService* service = createService(repo);

	assert(storeProductService(service, "1", "a", "b", "3") == 0);
	destroyService(service);
}
void storeProductService_InvalidProduct_ReturnsErrorCode1()
{
	ProductRepository* repo = createProductRepository();
	ProductService* service = createService(repo);

	storeProductService(service, "1", "a", "b", "3");
	assert(storeProductService(service, "1", "a", "b", "3") == 1);
	destroyService(service);
}
void removeProductService_ValdidProduct_RemovesProduct()
{
	ProductRepository* repo = createProductRepository();
	ProductService* service = createService(repo);

	storeProductService(service, "1", "a", "b", "3");
	assert(removeProductService(service, "1") == 0);
	destroyService(service);
}
void removeProductService_InvalidProduct_ReturnsErrorCode1()
{
	ProductRepository* repo = createProductRepository();
	ProductService* service = createService(repo);

	assert(removeProductService(service, "1") == 1);
	destroyService(service);
}

void testService()
{
	storeProductService_ValidProduct_StoredProduct();
	storeProductService_InvalidProduct_ReturnsErrorCode1();
	removeProductService_ValdidProduct_RemovesProduct();
	removeProductService_InvalidProduct_ReturnsErrorCode1();
	
}
void undo_RepositoryAfterStoredElement_RemovesElement()
{
	ProductRepository* repo = createProductRepository();
	ProductService* service = createService(repo);

	storeProductService(service, "1", "state", "type", "1");
	assert(undoService(service) == 0);
	destroyService(service);
}
void undo_NoMorePossibleUndos_ErrorCode1()
{
	ProductRepository* repo = createProductRepository();
	ProductService* service = createService(repo);

	storeProductService(service, "1", "state", "type", "1");
	undoService(service);
	assert(undoService(service) == 1);
	destroyService(service);
}
void redo_AfterUndo_SuccessfulRedo()
{
	ProductRepository* repo = createProductRepository();
	ProductService* service = createService(repo);

	storeProductService(service, "1", "state", "type", "1");
	undoService(service);
	
	assert(redoService(service) == 0);
	destroyService(service);
}
void redo_NoMorePossibleRedos_ErrorCode1()
{
	ProductRepository* repo = createProductRepository();
	ProductService* service = createService(repo);

	storeProductService(service, "1", "state", "type", "1");
	undoService(service);
	redoService(service);

	assert(redoService(service) == 1);
	destroyService(service);
}
void testUndoRedo()
{
	undo_RepositoryAfterStoredElement_RemovesElement();
	undo_NoMorePossibleUndos_ErrorCode1();
	redo_AfterUndo_SuccessfulRedo();
	redo_NoMorePossibleRedos_ErrorCode1();
}

void testAll()
{
	testProduct();
	testRepository();
	testService();
	testUndoRedo();
	printf("\nThe tests were succesfull!\n");
}
