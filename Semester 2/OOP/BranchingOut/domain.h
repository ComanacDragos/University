#pragma once

#define StringLength 256
// the maximum lenghth of state and type of a product

typedef struct {
	int catalogueNumber, value;
	char state[StringLength], type[StringLength];
}Product;

//returns a product with the given properties
Product createProduct(int catalogueNumber, char state[], char type[], int value);

int getCatalogueNumber(Product* product);

char* getState(Product* product);

char* getType(Product* product);

int getValue (Product* product);

void updateState(Product* product, char newState[]);

void updateType(Product* product, char newType[]);

void updateValue(Product* product, int newValue);

void printProduct(Product* product);

