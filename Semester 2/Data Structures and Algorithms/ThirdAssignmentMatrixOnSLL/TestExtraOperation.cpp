#include <assert.h>
#include "Matrix.h"
#include "TestExtraOperation.h"
#include <iostream>
#include <exception>

void testOperation()
{
	std::cout << "Test extra operation\n";
	Matrix m(4, 4);
	m.modify(1, 1, 3);
	m.modify(1, 2, 4);
	m.modify(1, 3, 5);
	m.modify(3, 3, 4);

	assert(m.numberOfNonZeroElems(0) == 0);
	assert(m.numberOfNonZeroElems(1) == 3);
	assert(m.numberOfNonZeroElems(2) == 0);
	assert(m.numberOfNonZeroElems(3) == 1);

	m.modify(3, 3, 0);

	assert(m.numberOfNonZeroElems(0) == 0);
	assert(m.numberOfNonZeroElems(1) == 3);
	assert(m.numberOfNonZeroElems(2) == 0);
	assert(m.numberOfNonZeroElems(3) == 0);


	Matrix m2(4, 5);
	assert(m2.numberOfNonZeroElems(3) == 0);

	m2.modify(3, 2, 3);
	assert(m2.numberOfNonZeroElems(3) == 1);

	try {
		m.numberOfNonZeroElems(-1);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}

	try {
		m.numberOfNonZeroElems(4);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}

}
