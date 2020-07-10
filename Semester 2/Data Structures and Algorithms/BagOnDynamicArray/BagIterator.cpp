#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	//TODO - Implementation
	currentPos = 0;
	currentFrequency = 1;
}

void BagIterator::first() {
	//TODO - Implementation
	currentPos = 0;
	currentFrequency = 1;
}


void BagIterator::next() {
	//TODO - Implementation
	if (valid() == false)
		throw exception("Invalid position");
	if (currentFrequency == bag.frequencies[currentPos])
	{
		currentPos += 1;
		currentFrequency = 1;
	}
	else
	{
		currentFrequency += 1;
	}
	while (bag.frequencies[currentPos] == 0)
		currentPos++;
}


bool BagIterator::valid() const {
	//TODO - Implementation
	if (bag.lenght == 0)
		return false;
	//return currentPos < bag.capacity;//&& currentFrequency <= bag.frequencies[currentPos];
	if (currentPos < bag.capacity)
		return true;
	return false;
}



TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
	if (valid() == false)
		throw exception("Invalid position");
	return bag.min + currentPos;
}
