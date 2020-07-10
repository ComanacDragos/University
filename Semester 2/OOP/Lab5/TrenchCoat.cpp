#include "TrenchCoat.h"

TrenchCoat::TrenchCoat()
{
	this->name = "";
	this->size = "";
	this->photographSource = "";
	this->price = -1;
}

TrenchCoat::TrenchCoat(const std::string& name, const std::string& size, const std::string photographSource, const int price)
{
	this->name = name;
	this->size = size;
	this->photographSource = photographSource;
	this->price = price;
}

TrenchCoat::TrenchCoat(const TrenchCoat& trenchCoat)
{
	this->name = trenchCoat.name;
	this->photographSource = trenchCoat.photographSource;
	this->price = trenchCoat.price;
	this->size = trenchCoat.size;
}

TrenchCoat& TrenchCoat::operator=(const TrenchCoat& trenchCoat)
{
	if (this == &trenchCoat)
		return *this;

	
	this->price = trenchCoat.price;

	this->name = trenchCoat.name;
	
	this->size = trenchCoat.size;

	this->photographSource = trenchCoat.photographSource;


	return *this;
}

std::string TrenchCoat::getName() const
{
	return this->name;
}

std::string TrenchCoat::getSize() const
{
	return this->size;
}

std::string TrenchCoat::getPhotographSource() const
{
	return this->photographSource;
}

int TrenchCoat::getPrice() const
{
	return this->price;
}

bool TrenchCoat::operator==(const TrenchCoat& trenchCoat)
{
	if (this->name.compare(trenchCoat.name) == 0)
		return true;
	return false;
}

std::string TrenchCoat::to_string()
{
	return this->name + " " + this->size + " " + std::to_string(this->price) + " " + this->photographSource;
}

void TrenchCoat::openInBrowser()
{
	//ShellExecuteA(NULL, NULL, "chrome.exe", this->getPhotographSource().c_str(), NULL, SW_SHOWMAXIMIZED);
}
