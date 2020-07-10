#include <crtdbg.h>

#include "tests.h"
#include "CommandUserInterface.h"

int main()
{
	{
		testAll();
		CoatRepository coatRepository;
		CoatService coatService{ coatRepository };
		CommandUserInterface commandUserInterface{ coatService };
		commandUserInterface.startProgram();
	}
	_CrtDumpMemoryLeaks();
	

	return 0;
}