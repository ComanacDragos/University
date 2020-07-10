#include "Test.h"

void testNrCars()
{
	std::ofstream fout{ "test.txt" };
	fout << "car1|model1|2001|red\n";
	fout << "car2|model2|2001|red\n";
	fout << "car1|model3|2001|red\n";
	fout.close();
	Service srv{ "test.txt" };
	assert(srv.nrCars("car1") == 2);
	assert(srv.nrCars("car2") == 1);

	std::ofstream fout2{ "test.txt" };
	fout2.close();
}
