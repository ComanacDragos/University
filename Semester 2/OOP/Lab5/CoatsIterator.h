#pragma once
#include "DynamicVector.h"
#include "TrenchCoat.h"

class CoatsIterator
{
private:
	DynamicVector<TrenchCoat> coats;
	int currentPosition;

public:
	CoatsIterator();

	CoatsIterator(const DynamicVector<TrenchCoat>& coats);

	CoatsIterator(const CoatsIterator& coatsIterator);

	CoatsIterator& operator=(const CoatsIterator& coatsIterator);

	~CoatsIterator() {};

	void first();

	bool valid();

	void next();

	TrenchCoat getCurrent();
};

