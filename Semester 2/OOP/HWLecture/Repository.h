#pragma once
#include "Aircraft.h"
#include <vector>
#include <memory>

class Repository
{
private:
	std::vector<std::shared_ptr<Aircraft>> aircrafts;

public:
	void add(std::shared_ptr<Aircraft>& aircraft);

	std::vector<std::weak_ptr<Aircraft>> const& getAircraftsActivity(const std::string activity);

	std::vector<std::shared_ptr<Aircraft>> const& getAircraftsAltitude(int altitude);

};

