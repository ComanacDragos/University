#pragma once
#include "Domain.h"

class Repository
{
private:
	std::vector<Astronomer> astronomers;
	std::vector<Star> stars;

	std::string starFile;
public:
	Repository(const std::string& astronomersFile, const std::string& starFile) :starFile{ starFile }
	{
		std::ifstream fin{ astronomersFile };
		std::string line;
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line,',');
			this->astronomers.push_back(Astronomer{ tokens[0],tokens[1] });
		}
		fin.close();
		fin.open(this->starFile, 0);
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->stars.push_back(Star{ tokens[0],tokens[1],stoi(tokens[2]), stoi(tokens[3]),stoi(tokens[4]) });
		}
		fin.close();

	}

	std::vector<Star> getStars() { return this->stars; }
	std::vector<Astronomer> getAstronomers() { return this->astronomers; }


	//Adds the star object to the vector of stars
	//Throws exception if there is another star with the same name
	void addStar(Star& star)
	{
		for (Star& s : this->stars)
			if (s.getName() == star.getName())
				throw Exceptions{ "Existent Star" };
		this->stars.push_back(star);

	}

	std::vector<Star> getStarByName(const std::string& name)
	{
		std::vector<Star> starsByName;
		for (Star& s : this->stars)
			if (s.getName().find(name) != std::string::npos)
				starsByName.push_back(s);
		return starsByName;
	}

	Star getStar(const std::string& name)
	{
		for (Star& s : this->stars)
			if (s.getName() == name)
				return s;
	}

	~Repository()
	{
		std::sort(this->stars.begin(), this->stars.end(), [](Star& s1, Star& s2) {return s1.getConstelation() < s2.getConstelation(); });
		std::ofstream fout{ this->starFile };
		for (Star& s : this->stars)
			fout << s.to_string(',') << '\n';
		fout.close();
	}
};

