#pragma once
#include <vector>
#include "Aircraft.h"


class Repository
{
private:
	std::vector<Aircraft*> aircrafts;

public:
	void add(Aircraft* aircraft);

	const std::vector<Aircraft*> getAircrafts();

	~Repository();
};

