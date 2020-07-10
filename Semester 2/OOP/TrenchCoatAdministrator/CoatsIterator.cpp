#include "CoatsIterator.h"

CoatsIterator::CoatsIterator()
{
	this->currentPosition = 0;
}

CoatsIterator::CoatsIterator(const std::vector<TrenchCoat>& coats)
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
	if (this->coats.size() == 0)
		return false;
	return true;
}

void CoatsIterator::next()
{
	if (valid())
	{
		if (this->currentPosition == this->coats.size() - 1)
			this->first();
		else
			this->currentPosition += 1;
	}
	else
		throw BadPosition("There are no coats in the repository");
}

TrenchCoat CoatsIterator::getCurrent()
{
	if(valid())
	{
	return this->coats[this->currentPosition];
	}
	else
		throw BadPosition("There are no coats in the repository");
}

