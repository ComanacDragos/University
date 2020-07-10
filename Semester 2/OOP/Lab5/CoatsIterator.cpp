#include "CoatsIterator.h"

CoatsIterator::CoatsIterator()
{
	this->currentPosition = 0;
}

CoatsIterator::CoatsIterator(const DynamicVector<TrenchCoat>& coats)
{
	this->currentPosition = 0;
	this->coats = coats;
}

CoatsIterator::CoatsIterator(const CoatsIterator& coatsIterator)
{
	this->coats = coatsIterator.coats;
	this->currentPosition = coatsIterator.currentPosition;
}

CoatsIterator& CoatsIterator::operator=(const CoatsIterator& coatsIterator)
{
	if (this == &coatsIterator)
		return *this;
	this->coats = coatsIterator.coats;
	this->currentPosition = coatsIterator.currentPosition;
	return *this;
}

void CoatsIterator::first()
{
	this->currentPosition = 0;
}

bool CoatsIterator::valid()
{
	if (this->currentPosition < 0 || this->currentPosition >= this->coats.getLength())
		return false;
	return true;
}

void CoatsIterator::next()
{
	if (valid())
	{
		if (this->currentPosition == this->coats.getLength() - 1)
			this->first();
		else
			this->currentPosition += 1;
	}
}

TrenchCoat CoatsIterator::getCurrent()
{
	return this->coats.getElement(this->currentPosition);
}

