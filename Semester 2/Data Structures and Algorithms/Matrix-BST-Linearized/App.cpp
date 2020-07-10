
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;

#include <assert.h>

int main() {
	testExtra();
	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
}