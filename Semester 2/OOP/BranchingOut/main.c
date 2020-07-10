#include <stdio.h>
#include <crtdbg.h>
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "tests.h"
#include "UserInterface.h"

#define _CRTDBG_MAP_ALLOC





int main()
{
	
	testAll();
	
	ProductRepository* productRepository = createProductRepository();
	ProductService* productService = createService(productRepository);
	CommandBasedUI* commandBasedUI = createUI(productService);
	
	startProgram(commandBasedUI);

	destroyUserInterface(commandBasedUI);

	
	_CrtDumpMemoryLeaks();
	return 0;
}