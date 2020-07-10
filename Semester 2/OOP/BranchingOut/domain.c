#include "domain.h"
#include <string.h>
#include <stdlib.h>

Product createProduct(int catalogueNumber, char state[], char type[], int value)
{
	Product product;
	product.catalogueNumber = catalogueNumber;
	product.value = value;

	strcpy(product.state, state);
	strcpy(product.type, type);

	return product;
}

int getCatalogueNumber(Product* product)
{
	return product->catalogueNumber;
}

char* getState(Product* product)
{
	return product->state;
}

char* getType(Product* product)
{
	return product->type;
}

int getValue(Product* product)
{
	return product->value;
}

void updateState(Product* product, char newState[])
{
	strcpy(product->state, newState);
}

void updateType(Product* product, char newType[])
{
	strcpy(product->type, newType);
}

void updateValue(Product* product, int newValue)
{
	product->value = newValue;
}

void printProduct(Product* product)
{
	printf("%d %s %s %d\n", product->catalogueNumber, product->state, product->type, product->value);
}
