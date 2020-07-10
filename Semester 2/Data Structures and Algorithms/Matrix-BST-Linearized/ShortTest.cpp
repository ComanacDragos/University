#include <assert.h>
#include "Matrix.h"
#include "ShortTest.h"
#include <iostream>

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
}

void testExtra()
{
	Matrix m(4, 4);
	std::pair<int, int> pNull{ -1,-1 };

	assert(m.positionOf(8) == pNull);
	
	m.modify(1, 1, 5);

	std::pair<int,int> p1{ 1,1 };
	assert(m.positionOf(5) == p1);

	m.modify(0, 1, 5);
	assert(m.positionOf(5) == p1);

	std::pair<int, int> p2{ 2,1 };
	m.modify(2, 1, 7);
	assert(m.positionOf(7) == p2);

	assert(m.positionOf(8) == pNull);


	
	std::cout << "TestExtra\n";
}
