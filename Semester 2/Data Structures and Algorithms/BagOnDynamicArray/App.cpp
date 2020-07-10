#include "Bag.h"
#include "BagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

#include<vector>
#include <assert.h>

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();
	

	return 0;
}