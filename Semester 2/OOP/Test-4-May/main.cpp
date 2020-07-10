#include "UI.h"
#include <crtdbg.h>

int main()
{
	{
		UI ui;
		ui.startProgram();
	}

	_CrtDumpMemoryLeaks();
}