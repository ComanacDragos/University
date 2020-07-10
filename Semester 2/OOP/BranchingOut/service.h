#pragma once
#include "repository.h"

typedef struct
{
	Product** productLists;
	int* lenghts;
	int* capacities;
	int lenght, capacity, currentRepositoryIndex;
}UndoRedoListOfLists;

typedef struct
{
	ProductRepository* productRepository;
	UndoRedoListOfLists* undoRedoListOfLists;
}ProductService;

ProductService* createService(ProductRepository* productRepository);

/*
Creates a product and adds it to the repository
Returns 0 if the operation was succesful and 1 if the product already exists in repository
*/
int storeProductService(ProductService* productService, char catalogueNumber[], char state[], char type[], char value[]);

/*
Removes from the repository a product with a given catalogue number
Returns 0 if the operation was succesful and 1 if the product does not exist
*/
int removeProductService(ProductService* productService, char catalogueNumber[]);

/*
Returns the product at the index i in repository
*/
Product getProductFromRepository(ProductService* productService, int index);

/*
Updates the statem type and value of a product
*/
void updateProductService(ProductService* productService, char catalogueNumber[], char state[], char type[], char value[]);

/*
Returns the number of products in repository
*/
int repositoryLengthService(ProductService* productService);


ProductRepository* listMaximumPotencyValueService(ProductService* productService, char maximumPotencyValue[]);

void destroyService(ProductService* productService);

int undoService(ProductService* productService);

int redoService(ProductService* productService);


void copyRepository(ProductRepository* destinationRepository, UndoRedoListOfLists* undoRedoListOfLists);

ProductRepository* createUndoRedoListOfLists();



void storeInUndoRedoListOfListsRepository(UndoRedoListOfLists* undoRedoListOfLists, ProductRepository* productRepository);

/*
Deletes all repositories between a certain index and the end
*/
void deleteFromUndoRedoListOfListsRepositories(UndoRedoListOfLists* undoRedoListOfLists, int startIndex);

void increaseUndoRedoListOfLists(UndoRedoListOfLists* undoRedoListOfLists);

void shrinkUndoRedoListOfLists(UndoRedoListOfLists* undoRedoListOfLists);

Product* getCurrentProductRepositoryFromListOfLists(UndoRedoListOfLists* undoRedoListOfLists);

int getCurrentProductRepositoryLenghtFromListOfLists(UndoRedoListOfLists* undoRedoListOfLists);

int getCurrentProductRepositoryCapacityFromListOfLists(UndoRedoListOfLists* undoRedoListOfLists);


void destroyUndoRedoListOfLists(UndoRedoListOfLists* undoRedoListOfLists);


