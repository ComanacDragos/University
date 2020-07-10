#include "Repo.h"

void Repo::addMeci(Meci& meci)
{
	auto it = std::find(this->meciuri.begin(), this->meciuri.end(), meci);
	if (it != this->meciuri.end())
		throw std::exception{ "Meci existent" };
	this->meciuri.push_back(meci);


	auto it1 = std::find(this->echipe.begin(), this->echipe.end(), meci.getAcasa());
	
	if (it1 == this->echipe.end())
		this->echipe.push_back(meci.getAcasa());

	auto it2 = std::find(this->echipe.begin(), this->echipe.end(), meci.getDeplasare());

	if (it2 == this->echipe.end())
		this->echipe.push_back(meci.getDeplasare());
}

std::vector<Meci> Repo::getMeciuri()
{
	return this->meciuri;
}
