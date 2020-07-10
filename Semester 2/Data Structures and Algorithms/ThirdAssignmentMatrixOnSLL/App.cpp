
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "TestExtraOperation.h"

using namespace std;


int main() {

	testOperation();
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}