#include "repository.h"
#include <stdio.h>

ProductRepository* createProductRepository()
{
	ProductRepository* productRepository = (ProductRepository*)malloc(sizeof(ProductRepository));

	if (productRepository == NULL)
		return NULL;

	productRepository->capacity = RepositoryCapacity;
	productRepository->length = 0;

	productRepository->products = (Product*)malloc(RepositoryCapacity * sizeof(Product));
	
	return productRepository;
}

int storeProduct(ProductRepository* productRepository, Product product)
{
	int productIndex = findProduct(productRepository, getCatalogueNumber(&product));
	if (productIndex == -1)
	{
		if (productRepository->length == productRepository->capacity)
			increaseRepositorySize(productRepository);

		productRepository->products[productRepository->length] = product;
		productRepository->length += 1;
		return 0;
	}
	return 1;
}

int removeProduct(ProductRepository* productRepository, int catalogueNumber)
{
	int productIndex = findProduct(productRepository, catalogueNumber);
	if(productIndex != -1)
	{
		int i;
		for (i = productIndex; i < productRepository->length; i++)
			productRepository->products[i] = productRepository->products[i + 1];
			productRepository->length -= 1;
			
			if (productRepository->length == productRepository->capacity / 2)
				shrinkRepositorySize(productRepository);
			
			return 0;
	}
	return 1;
}

int findProduct(ProductRepository* productRepository, int catalogueNumber)
{
	int i;
	for(i=0; i < productRepository->length; i++)
		if(getCatalogueNumber(&productRepository->products[i]) == catalogueNumber)
			return i;
	return -1;
}

Product* getProduct(ProductRepository* productRepository, int index)
{
	if (index < 0 || index > productRepository->length)
		return NULL;

	return &productRepository->products[index];
}

void updateProduct(ProductRepository* productRepository, int catalogueNumber, char newState[], char newType[], int newValue)
{
	int index = findProduct(productRepository, catalogueNumber);
	Product* product = getProduct(productRepository, index);
	updateState(product, newState);
	updateType(product, newType);
	updateValue(product, newValue);
}

int repositoryLength(ProductRepository* productRepository)
{
	return productRepository->length;
}

void increaseRepositorySize(ProductRepository* productRepository)
{
	productRepository->capacity *= 2;
	Product* largerProductRepository = (Product*)malloc(sizeof(Product) * productRepository->capacity);

	if (largerProductRepository == NULL)
		return;

	for (int i = 0; i < productRepository->length; i++)
		largerProductRepository[i] = productRepository->products[i];

	free(productRepository->products);
	productRepository->products = largerProductRepository;
}

void shrinkRepositorySize(ProductRepository* productRepository)
{
	productRepository->capacity /= 2;
	Product* smallerProductRepository = (Product*)malloc(sizeof(Product) * productRepository->capacity);

	if (smallerProductRepository == NULL)
		return;

	for (int i = 0; i < productRepository->length; i++)
		smallerProductRepository[i] = productRepository->products[i];

	free(productRepository->products);
	productRepository->products = smallerProductRepository;
}

void destroyRepository(ProductRepository* productRepository)
{
	free(productRepository->products);
	free(productRepository);
}
