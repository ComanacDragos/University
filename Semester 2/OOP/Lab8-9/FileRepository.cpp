#include "FileRepository.h"

FileRepository::FileRepository(const std::string& filePath)
{
	this->filePath = filePath;
}

void FileRepository::storeCoat(const TrenchCoat& coat)
{
	std::vector<TrenchCoat> coats = this->loadCoatsFromFile();
	if (std::find(coats.begin(), coats.end(), coat) != coats.end())
		throw ExistentTrenchCoat{ "Coat already exists\n" };

	coats.push_back(coat);
	this->storeCoatsToFile(coats);
}

void FileRepository::deleteCoat(const std::string& name)
{
	std::vector<TrenchCoat> coats = this->loadCoatsFromFile();
	auto iterator = find(coats.begin(), coats.end(), TrenchCoat(name, "size", "source", 0));
	if (iterator == coats.end())
		throw InexistentTrenchCoat{ "Coat doesn't exist\n" };

	coats.erase(iterator);
	this->storeCoatsToFile(coats);
}

void FileRepository::updateCoat(const TrenchCoat& coat)
{
	std::vector<TrenchCoat> coats = this->loadCoatsFromFile();
	auto iterator = find(coats.begin(), coats.end(), coat);
	if (iterator == coats.end())
		throw InexistentTrenchCoat{ "Coat doesn't exist\n" };

	*iterator = coat;
	this->storeCoatsToFile(coats);
}

TrenchCoat FileRepository::getCoatFromRepository(int position)
{
	std::vector<TrenchCoat> coats = this->getAllCoats();
	if (position < 0 || position >= (int)coats.size())
		throw BadPosition{ "Invalid position\n" };

	return *(coats.begin() + position);
}

TrenchCoat FileRepository::findCoatFromRepository(const std::string& name)
{
	std::vector<TrenchCoat> coats = this->getAllCoats();
	auto iterator = find(coats.begin(), coats.end(), TrenchCoat(name, "size", "source", 0));
	if (iterator == coats.end())
		throw InexistentTrenchCoat{ "Coat doesn't exist\n" };

	return *iterator;
}

bool FileRepository::existentCoat(const std::string& name)
{
	std::vector<TrenchCoat> coats = this->getAllCoats();
	auto iterator = find(coats.begin(), coats.end(), TrenchCoat(name, "size", "source", 0));
	if (iterator == coats.end())
		return false;

	return true;
}

int FileRepository::getRepositoryLength()
{
	return this->loadCoatsFromFile().size();
}

std::vector<TrenchCoat> FileRepository::getAllCoats()
{
	return this->loadCoatsFromFile();
}


void FileRepository::setPath(std::string filePath)
{
	this->filePath = filePath;
	//this->clearFile();
}

void FileRepository::clearFile()
{
	std::ofstream fout(this->filePath);
	fout.close();
}

void FileRepository::openFile()
{
	system(this->filePath.c_str());
}

void CSVFileRepository::openFile()
{
	ShellExecuteA(NULL, NULL, "notepad.exe", this->filePath.c_str(), NULL, SW_SHOWMAXIMIZED);
}

void CSVFileRepository::storeCoatsToFile(const std::vector<TrenchCoat>& coats)
{
	std::ofstream fout (this->filePath, std::ios::trunc | std::ios::out);
	for (const TrenchCoat& coat : coats)
		fout << *(static_cast<const CSVTrenchCoat*>(&coat));
	fout.close();
}

std::vector<TrenchCoat> CSVFileRepository::loadCoatsFromFile()
{
	std::ifstream fin(this->filePath, std::ios::in);

	std::vector<TrenchCoat> coats;
	CSVTrenchCoat currentCoat;

	while (fin >> currentCoat)
		coats.push_back(currentCoat);

	fin.close();
	return coats;
}

void HTMLFileRepository::openFile()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->filePath.c_str(), NULL, SW_SHOWMAXIMIZED);
}

void HTMLFileRepository::storeCoatsToFile(const std::vector<TrenchCoat>& coats)
{
	std::ofstream fout{ this->filePath };
	fout << "<!DOCTYPE html>\n";
	fout << "<html>\n";
	fout << "<head>\n" << "<title>Coats</title>\n" << "</head>\n";
	fout << "<body>\n" << "<table border=\"1\">\n";
	
	fout << "<tr>\n";
	fout << "<td>" << "Name" << "</td>\n";
	fout << "<td>" << "Size" << "</td>\n";
	fout << "<td>" << "Price" << "</td>\n";
	fout << "<td>" << "Photograph Source" << "</td>\n";
	fout << "</tr>\n";


	for (const TrenchCoat& coat : coats)
		fout << *(static_cast<const HTMLTrenchCoat*>(&coat));

	fout << "</table>\n";
	fout << "</body>\n";
	fout << "</html>\n";

	fout.close();
}

std::vector<TrenchCoat> HTMLFileRepository::loadCoatsFromFile()
{
	std::ifstream fin{ this->filePath };
	std::vector<TrenchCoat> coats;
	std::string line;
	HTMLTrenchCoat currentCoat;
	int numberOfLinesToSkip = 13;
	for (int i = 0; i < numberOfLinesToSkip; i++)
		std::getline(fin, line);

	while (fin >> currentCoat)
		if (currentCoat.getName().size() != 0)
		{
			coats.push_back(currentCoat);
			currentCoat = HTMLTrenchCoat{};
		}
	fin.close();
	return coats;
}
