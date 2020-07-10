#include "UI.h"
#include "Aircraft.h"
#include <vector>
#include <crtdbg.h>

int main()
{
	{
	Repository repo;
	Service srv{ repo };
	UI ui{ srv };
	ui.start();
	}
	_CrtDumpMemoryLeaks();
}