#pragma once
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>


class TrenchCoat
{
protected:
	std::string name;
	std::string size;
	std::string photographSource;

	int price;

public:
	// default constructor
	TrenchCoat();

	// constructor with parameters
	TrenchCoat(const std::string& name, const std::string& size, const std::string photographSource, const int price);

	TrenchCoat(const TrenchCoat& trenchCoat);

	TrenchCoat& operator= (const TrenchCoat & trenchCoat);

	virtual ~TrenchCoat(){}

	std::string getName() const;
	std::string getSize() const;
	std::string getPhotographSource() const;
	int getPrice() const;
	
	//returns true if the trench coats are the same, false otherwise
	bool operator==(const TrenchCoat& trenchCoat);

	std::string to_string();
};

class CSVTrenchCoat : public TrenchCoat
{
public:
	CSVTrenchCoat() :TrenchCoat{} {}

	CSVTrenchCoat(const std::string& name, const std::string& size, const std::string photographSource, const int price) :TrenchCoat{ name, size, photographSource, price } {}

	~CSVTrenchCoat() {}
};

class HTMLTrenchCoat : public TrenchCoat
{
public:
	HTMLTrenchCoat() :TrenchCoat{} {}

	HTMLTrenchCoat(const std::string& name, const std::string& size, const std::string photographSource, const int price) :TrenchCoat{ name, size, photographSource, price } {}

	~HTMLTrenchCoat() {}
};

//returns a vector composed of all words delimited by space and a delimiter
std::vector<std::string> tokenize(std::string str,const char delimiter);

std::istream& operator>>(std::istream& istream, CSVTrenchCoat& coat);

std::istream& operator>>(std::istream& istream, HTMLTrenchCoat& coat);

std::ostream& operator<<(std::ostream& ostream, const TrenchCoat& coat);

std::ostream& operator<<(std::ostream& ostream, const CSVTrenchCoat& coat);

std::ostream& operator<<(std::ostream& ostream, const HTMLTrenchCoat& coat);
