#include "Repo.h"

void Repo::addMeci(Meci& meci)
{
	auto it = std::find(this->meciuri.begin(), this->meciuri.end(), meci);
	if (it != this->meciuri.end())
		throw std::exception{ "Meci existent" };
	this->meciuri.push_back(meci);

	std::ofstream fout{ "meciuri.txt" };
	for (auto& m : this->meciuri)
		fout << m.to_string() << "\n";
}

std::vector<Meci> Repo::getMeciuri()
{
	return this->meciuri;
}
