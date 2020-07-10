#include "ShortTest.h"
#include <assert.h>
#include <iostream>
#include "Set.h"
#include "SetIterator.h"

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0); 
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1)==false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);


	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

}

void testExtraOperation()
{
	Set s;
	s.add(1);
	s.add(2);
	s.add(3);
	s.add(4);

	auto it = s.iterator();

	it.next();
	assert(it.remove() == 2);
	assert(it.getCurrent() == 3);
	assert(s.size() == 3);
	assert(s.search(2) == false);

	assert(it.remove() == 3);
	assert(it.getCurrent() == 4);
	assert(s.size() == 2);
	assert(s.search(3) == false);


	assert(it.remove() == 4);
	assert(s.size() == 1);
	assert(s.search(4) == false);

	try
	{
		it.getCurrent();
		assert(false);
	}
	catch (std::exception ex)
	{
		assert(true);
	}

	Set s2;


	s2.add(1);
	s2.add(2);
	s2.add(3);
	s2.add(4);
	s2.add(5);

	auto it2 = s2.iterator();
	for (int i = 1; i < 5; i++)
	{
		assert(it2.remove() == i);
		assert(it2.getCurrent() == i + 1);
		assert(s2.size() == 5 - i);
		assert(s2.search(i) == false);
	}
	assert(it2.getCurrent() == 5);
	assert(s2.size() == 1);
	assert(it2.remove() == 5);
	assert(s2.size() == 0);

	try
	{
		it2.getCurrent();
		assert(false);
	}
	catch (std::exception ex)
	{
		assert(true);
	}


	std::cout << "Extra operation successful\n";

}


