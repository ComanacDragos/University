#pragma once
#include "Repo.h"

class Service
{
private:
	Repo& repo;

public:
	Service(Repo& repo) :repo{ repo } {}

	void add(int idMeci, const std::string& echpaAcasa, const std::string numeEchpaDeplasare, int pctAcasa, int pctDeplasare);

	std::vector<Meci> getMeciuri();

};

