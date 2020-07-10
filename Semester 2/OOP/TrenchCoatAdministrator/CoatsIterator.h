#pragma once
#include <vector>
#include "TrenchCoat.h"
#include "Exceptions.h"

class CoatsIterator
{
private:
	std::vector<TrenchCoat> coats;
	int currentPosition;

public:
	CoatsIterator();

	CoatsIterator(const std::vector<TrenchCoat>& coats);

	CoatsIterator(const CoatsIterator& coatsIterator);

	CoatsIterator& operator=(const CoatsIterator& coatsIterator);

	~CoatsIterator() {};

	void first();

	bool valid();

	void next();

	TrenchCoat getCurrent();
};

