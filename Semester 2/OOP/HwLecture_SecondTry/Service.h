#pragma once
#include "Repository.h"
#include <fstream>

class Service
{
private:
	Repository repo;

public:
	Service(Repository repo):repo(repo){}

	void addHelicopter(const std::string& id, const std::string& model, const std::string& maxAltitude, const std::string& isPrivate);

	void addPlane(const std::string& id, const std::string& model, const std::string& maxAltitude, const std::string& isPrivate, const std::string& mainWings);

	void addBalloon(const std::string& id, const std::string& model, const std::string& maxAltitude, const std::string& maxWeight);

	const std::vector<Aircraft*> filterModel(std::string model);

	const std::vector<Aircraft*> filterAltitude(std::string altitude);

	~Service() {};
};

