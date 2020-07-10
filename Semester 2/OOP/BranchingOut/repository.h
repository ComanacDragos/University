#pragma once
#include "domain.h"
#include <stdlib.h>

#define RepositoryCapacity 2
//the number of elements the repository can hold

typedef struct
{
	Product* products;
	int length, capacity;

}ProductRepository;


ProductRepository* createProductRepository();

/*
Adds a product in the repository
Returns 1 if the product already exists, 0 otherwise
*/
int storeProduct(ProductRepository* productRepository, Product product);

/*
Removes a product with a given catalogue number
Returns 0 if the product doesn't exist, 1 otherwise
*/
int removeProduct(ProductRepository* productRepository, int catalogueNumber);

/*
Searches for a product with a given catalogue number
Returns the index of the product with the given catalogue number, -1 otherwise
*/
int findProduct(ProductRepository* productRepository, int catalogueNumber);


/*
Returns the address of a product with a given index in repository or NULL if the index is invalid
*/
Product* getProduct(ProductRepository* productRepository, int index);

/*
Updates the state, type and value of a product identified by a catalogue number
*/
void updateProduct(ProductRepository* productRepository,int catalogueNumber, char newState[], char newType[], int newValue);

/*
Returns the length of the repository(number of products)
*/
int repositoryLength(ProductRepository* productRepository);

void increaseRepositorySize(ProductRepository* productRepository);

void shrinkRepositorySize(ProductRepository* productRepository);

void destroyRepository(ProductRepository* productRepository);

