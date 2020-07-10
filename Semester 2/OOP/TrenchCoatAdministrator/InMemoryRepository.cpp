#include "InMemoryRepository.h"

void InMemoryRepository::storeCoat(const TrenchCoat& coat)
{
	if (std::find(this->coats.begin(), this->coats.end(), coat) != this->coats.end())
		throw ExistentTrenchCoat{ "Coat already exists\n" };

	this->coats.push_back(coat);
}

void InMemoryRepository::deleteCoat(const std::string& name)
{
	auto iterator = find(this->coats.begin(), this->coats.end(), TrenchCoat(name, "size", "source", 0));
	if (iterator == this->coats.end())
		throw InexistentTrenchCoat{ "Coat doesn't exist\n" };

	this->coats.erase(iterator);

}

void InMemoryRepository::updateCoat(const TrenchCoat& coat)
{
	auto iterator = find(this->coats.begin(), this->coats.end(), coat);
	if (iterator == this->coats.end())
		throw InexistentTrenchCoat{ "Coat doesn't exist\n" };

	*iterator = coat;
}

TrenchCoat InMemoryRepository::getCoatFromRepository(int position)
{
	if (position < 0 || position >= (int)this->coats.size())
		throw BadPosition{ "Invalid position\n" };

	return *(this->coats.begin() + position);
}

TrenchCoat InMemoryRepository::findCoatFromRepository(const std::string& name)
{
	auto iterator = find(this->coats.begin(), this->coats.end(), TrenchCoat(name, "size", "source", 0));
	if (iterator == this->coats.end())
		throw InexistentTrenchCoat{ "Coat doesn't exist\n" };

	return *iterator;
}

bool InMemoryRepository::existentCoat(const std::string& name)
{
	auto iterator = find(this->coats.begin(), this->coats.end(), TrenchCoat(name, "size", "source", 0));
	if (iterator == this->coats.end())
		return false;

	return true;
}

int InMemoryRepository::getRepositoryLength()
{
	return this->coats.size();
}

std::vector<TrenchCoat> InMemoryRepository::getAllCoats()
{
	return this->coats;
}
