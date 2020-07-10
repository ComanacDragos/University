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

std::vector<std::string> tokenize(std::string string, const char delimiter)
{
	std::vector<std::string> result;
	
	std::stringstream stringStream{ string };
	std::string token;

	while (std::getline(stringStream, token, delimiter))
		if (token.size() != 0)
		{
			std::stringstream tokenStringStream { token };
			while (std::getline(tokenStringStream, token, ' '))
				if(token.size() != 0)
					result.push_back(token);
		}

	return result;
}


std::istream& operator>>(std::istream& istream, CSVTrenchCoat& coat)
{
	std::string line;
	std::getline(istream, line);
	std::vector<std::string> tokens = tokenize(line, ',');

	if (tokens.size() != 4) // bad data
		return istream;

	std::string name{ tokens[0] };
	std::string size{ tokens[1] };
	std::string photographSource{ tokens[3] };
	std::string price{ tokens[2] };



	CSVTrenchCoat newCoat{ name, size, photographSource, stoi(price) };
	coat = newCoat;
	
	return istream;
}

std::istream& operator>>(std::istream& istream, HTMLTrenchCoat& coat)
{
	std::string line;
	std::getline(istream, line);

	if (line != "<tr>")
		return istream;

	std::vector<std::string> coatFields{ 4 };

	for (auto& field : coatFields)
	{
		std::getline(istream, field);
		field.erase(field.begin(), field.begin() + 4);
		field.erase(field.end()-5, field.end());
	}
	std::getline(istream, line);

	std::string name = coatFields[0];
	std::string size = coatFields[1];
	std::string price = coatFields[2];
	std::string photographSource = coatFields[3];

	photographSource.erase(photographSource.begin(), photographSource.begin() + 10);
	photographSource.erase(photographSource.end() - 11, photographSource.end());

	HTMLTrenchCoat newCoat{ name, size, photographSource, stoi(price)};

	coat = newCoat;

	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const TrenchCoat& coat)
{
	ostream << coat.getName() << " " << coat.getSize() << " " << coat.getPrice() << " " << coat.getPhotographSource() << std::endl;
	return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const CSVTrenchCoat& coat)
{
	ostream << coat.getName() << "," << coat.getSize() << "," << coat.getPrice() << "," << coat.getPhotographSource() << std::endl;
	return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const HTMLTrenchCoat& coat)
{
	ostream << "<tr>\n";
	ostream << "<td>" << coat.getName() << "</td>\n";
	ostream << "<td>" << coat.getSize() << "</td>\n";
	ostream << "<td>" << coat.getPrice() << "</td>\n";
	ostream << "<td>" << "<a href= \"" << coat.getPhotographSource() << "\"> Link</a></td>\n";
	ostream << "</tr>\n";
	return ostream;
}

