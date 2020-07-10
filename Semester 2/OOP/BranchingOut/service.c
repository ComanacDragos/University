#include "service.h"


ProductService* createService(ProductRepository* productRepository)
{
	ProductService* productService = (ProductService*)malloc(sizeof(ProductService));

	if (productService == NULL)
		return NULL;

	productService->productRepository = productRepository;
	
	productService->undoRedoListOfLists = createUndoRedoListOfLists();
	storeInUndoRedoListOfListsRepository(productService->undoRedoListOfLists, productRepository);

	return productService;
}

int storeProductService(ProductService* productService, char catalogueNumber[], char state[], char type[], char value[])
{
	Product newProduct = createProduct(atoi(catalogueNumber), state, type, atoi(value));

	int succes = storeProduct(productService->productRepository, newProduct);

	if (succes == 0)
		storeInUndoRedoListOfListsRepository(productService->undoRedoListOfLists, productService->productRepository);

	return succes;
}

int removeProductService(ProductService* productService, char catalogueNumber[])
{
	int succes = removeProduct(productService->productRepository, atoi(catalogueNumber));

	if (succes == 0)
		storeInUndoRedoListOfListsRepository(productService->undoRedoListOfLists, productService->productRepository);

	return succes;
}

Product getProductFromRepository(ProductService* productService, int index)
{
	return *getProduct(productService->productRepository, index);
}

void updateProductService(ProductService* productService, char catalogueNumber[], char state[], char type[], char value[])
{
	updateProduct(productService->productRepository, atoi(catalogueNumber), state, type, atoi(value));
	storeInUndoRedoListOfListsRepository(productService->undoRedoListOfLists, productService->productRepository);
}

int repositoryLengthService(ProductService* productService)
{
	return repositoryLength(productService->productRepository);
}

ProductRepository* listMaximumPotencyValueService(ProductService* productService, char maximumPotencyValue[])
{
	int maximumPotencyVal = atoi(maximumPotencyValue);

	ProductRepository* filteredProducts = createProductRepository();

	if (filteredProducts == NULL)
		return NULL;

	for (int i = 0; i < repositoryLength(productService->productRepository); i++)
	{
		Product currentProduct = getProductFromRepository(productService, i);
		if (getValue(&currentProduct) <= maximumPotencyVal)
			storeProduct(filteredProducts, currentProduct);
	}

	for(int i=0;i<repositoryLength(filteredProducts)-1;i++)
		for(int j=i+1;j<repositoryLength(filteredProducts);j++)
			if (strcmp(getState(getProduct(filteredProducts, i)), getState(getProduct(filteredProducts, j))) > 0)
			{
				Product auxiliaryInterchange = *getProduct(filteredProducts,i);
				*getProduct(filteredProducts, i) = *getProduct(filteredProducts, j);
				*getProduct(filteredProducts, j) = auxiliaryInterchange;
			}


	return filteredProducts;
}

void destroyService(ProductService* productService)
{
	destroyRepository(productService->productRepository);
	destroyUndoRedoListOfLists(productService->undoRedoListOfLists);
	free(productService);
}

int undoService(ProductService* productService)
{
	if (productService->undoRedoListOfLists->currentRepositoryIndex == 0)
		return 1;

	productService->undoRedoListOfLists->currentRepositoryIndex -= 1;

	//copyRepository(productService->productRepository, getCurrentProductRepositoryFromListOfLists(productService->undoRedoListOfLists));
	copyRepository(productService->productRepository, productService->undoRedoListOfLists);

	return 0;
}

int redoService(ProductService* productService)
{
	if (productService->undoRedoListOfLists->currentRepositoryIndex == productService->undoRedoListOfLists->lenght - 1)
		return 1;
	productService->undoRedoListOfLists->currentRepositoryIndex += 1;
	
	//copyRepository(productService->productRepository, getCurrentProductRepositoryFromListOfLists(productService->undoRedoListOfLists));
	copyRepository(productService->productRepository, productService->undoRedoListOfLists);

	return 0;
}

void copyRepository(ProductRepository* destinationRepository, UndoRedoListOfLists* undoRedoListOfLists)
{
	Product* copyOfProducts = (Product*)malloc(sizeof(Product) * getCurrentProductRepositoryCapacityFromListOfLists(undoRedoListOfLists));
	Product* sourceProducts = getCurrentProductRepositoryFromListOfLists(undoRedoListOfLists);

	for (int i = 0; i < getCurrentProductRepositoryLenghtFromListOfLists(undoRedoListOfLists); i++)
		copyOfProducts[i] = sourceProducts[i];

	free(destinationRepository->products);

	destinationRepository->products = copyOfProducts;
	destinationRepository->length = getCurrentProductRepositoryLenghtFromListOfLists(undoRedoListOfLists);
	destinationRepository->capacity = getCurrentProductRepositoryCapacityFromListOfLists(undoRedoListOfLists);
}


ProductRepository* createUndoRedoListOfLists()
{
	UndoRedoListOfLists* undoRedoListOfLists = (UndoRedoListOfLists*)malloc(sizeof(UndoRedoListOfLists));

	if (undoRedoListOfLists == NULL)
		return NULL;

	undoRedoListOfLists->capacity = 2;
	undoRedoListOfLists->lenght = 0;
	undoRedoListOfLists->currentRepositoryIndex = -1;
	undoRedoListOfLists->productLists = (Product**)malloc(undoRedoListOfLists->capacity * sizeof(Product*));

	undoRedoListOfLists->capacities = (int*)malloc(undoRedoListOfLists->capacity * sizeof(int));
	undoRedoListOfLists->lenghts = (int*)malloc(undoRedoListOfLists->capacity * sizeof(int));

	return undoRedoListOfLists;
}


void storeInUndoRedoListOfListsRepository(UndoRedoListOfLists* undoRedoListOfLists, ProductRepository* productRepository)
{

	if (undoRedoListOfLists->currentRepositoryIndex != undoRedoListOfLists->lenght - 1)
		deleteFromUndoRedoListOfListsRepositories(undoRedoListOfLists, undoRedoListOfLists->currentRepositoryIndex + 1);

	if (undoRedoListOfLists->lenght == undoRedoListOfLists->capacity)
		increaseUndoRedoListOfLists(undoRedoListOfLists);

	Product* copyProductList = (Product*)malloc(sizeof(Product) * productRepository->length);

		for (int i = 0; i < productRepository->length; i++)
			copyProductList[i] = *getProduct(productRepository, i);

	undoRedoListOfLists->productLists[undoRedoListOfLists->lenght] = copyProductList;
	undoRedoListOfLists->lenghts[undoRedoListOfLists->lenght] = productRepository->length;
	undoRedoListOfLists->capacities[undoRedoListOfLists->lenght] = productRepository->capacity;

	undoRedoListOfLists->lenght += 1;
	undoRedoListOfLists->currentRepositoryIndex += 1;

}

void deleteFromUndoRedoListOfListsRepositories(UndoRedoListOfLists* undoRedoListOfLists, int startIndex)
{
	for (int i = startIndex; i < undoRedoListOfLists->lenght; i++)
	{
		free(undoRedoListOfLists->productLists[i]);
		undoRedoListOfLists->productLists[i] = NULL;
	}
	undoRedoListOfLists->lenght = startIndex;
	undoRedoListOfLists->currentRepositoryIndex = startIndex - 1;
	if (undoRedoListOfLists->lenght == undoRedoListOfLists->capacity / 2)
		shrinkUndoRedoListOfLists(undoRedoListOfLists);
}


void increaseUndoRedoListOfLists(UndoRedoListOfLists* undoRedoListOfLists)
{
	undoRedoListOfLists->capacity *= 2;

	Product** largerProductLists = (Product**)malloc(undoRedoListOfLists->capacity * sizeof(Product*));
	int* largerLenghts = (int*)malloc(undoRedoListOfLists->capacity * sizeof(int));
	int* largerCapacities = (int*)malloc(undoRedoListOfLists->capacity * sizeof(int));

	if (largerProductLists == NULL)
		return NULL;

	for (int i = 0; i < undoRedoListOfLists->lenght; i++) {
		largerProductLists[i] = undoRedoListOfLists->productLists[i];
		largerLenghts[i] = undoRedoListOfLists->lenghts[i];
		largerCapacities[i] = undoRedoListOfLists->capacities[i];
	}
	free(undoRedoListOfLists->capacities);
	free(undoRedoListOfLists->lenghts);
	free(undoRedoListOfLists->productLists);
	undoRedoListOfLists->productLists = largerProductLists;
	undoRedoListOfLists->lenghts = largerLenghts;
	undoRedoListOfLists->capacities = largerCapacities;
}

void shrinkUndoRedoListOfLists(UndoRedoListOfLists* undoRedoListOfLists)
{

	undoRedoListOfLists->capacity /= 2;

	Product** smallerRepositories = (Product**)malloc(undoRedoListOfLists->capacity * sizeof(Product*));
	int* smallerLenghts = (int*)malloc(undoRedoListOfLists->capacity * sizeof(int));
	int* smallerCapacities = (int*)malloc(undoRedoListOfLists->capacity * sizeof(int));

	if (smallerRepositories == NULL)
		return NULL;

	for (int i = 0; i < undoRedoListOfLists->lenght; i++){
		smallerRepositories[i] = undoRedoListOfLists->productLists[i];
		smallerLenghts[i] = undoRedoListOfLists->lenghts[i];
		smallerCapacities[i] = undoRedoListOfLists->capacities[i];
	}
	free(undoRedoListOfLists->capacities);
	free(undoRedoListOfLists->lenghts);
	free(undoRedoListOfLists->productLists);

	undoRedoListOfLists->productLists = smallerRepositories;
	undoRedoListOfLists->lenghts = smallerLenghts;
	undoRedoListOfLists->capacities = smallerCapacities;
	
}

Product* getCurrentProductRepositoryFromListOfLists(UndoRedoListOfLists* undoRedoListOfLists)
{
	return undoRedoListOfLists->productLists[undoRedoListOfLists->currentRepositoryIndex];
}
int getCurrentProductRepositoryLenghtFromListOfLists(UndoRedoListOfLists* undoRedoListOfLists)
{
	return undoRedoListOfLists->lenghts[undoRedoListOfLists->currentRepositoryIndex];

}int getCurrentProductRepositoryCapacityFromListOfLists(UndoRedoListOfLists* undoRedoListOfLists)
{
	return undoRedoListOfLists->capacities[undoRedoListOfLists->currentRepositoryIndex];
}

void destroyUndoRedoListOfLists(UndoRedoListOfLists* undoRedoListOfLists)
{
	for (int i = 0; i < undoRedoListOfLists->lenght; i++)
		free(undoRedoListOfLists->productLists[i]);
	
	free(undoRedoListOfLists->capacities);
	free(undoRedoListOfLists->lenghts);
	free(undoRedoListOfLists->productLists);
	free(undoRedoListOfLists);
}

