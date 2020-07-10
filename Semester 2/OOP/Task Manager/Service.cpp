#include "Service.h"

void testService()
{
	std::ofstream fout{ "test.txt" };
	fout << "task1 100 1\n";
	fout << "task2 200 2\n";
	fout.close();
	Service srv{ "test.txt" };
	assert(srv.totalTime(1) == 100);
	assert(srv.totalTime(2) == 200);

	std::ofstream fout2{ "test.txt" };
	fout2.close();

}

