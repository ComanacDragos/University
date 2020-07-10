#pragma once
#include <string>
#include <string.h>
#include <Windows.h>
#include <shellapi.h>

class TrenchCoat
{
private:
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

	~TrenchCoat(){}

	std::string getName() const;
	std::string getSize() const;
	std::string getPhotographSource() const;
	int getPrice() const;
	
	//returns true if the trench coats are the same, false otherwise
	bool operator==(const TrenchCoat& trenchCoat);

	std::string to_string();

	void openInBrowser();

};

