#include "Service.h"

Service::Service(const std::string& file):file{file}
{
	std::ifstream fin{ this->file };

	std::string line;
	while (std::getline(fin, line))
	{
		std::vector<std::string> tokens = tokenize(line, '|');
		Vegetable vegetable{ tokens[0], tokens[1], tokenize(tokens[2],',') };
		this->vegetables.push_back(vegetable);

		auto it = std::find(this->families.begin(), this->families.end(), tokens[0]);
		if (it == this->families.end())
			this->families.push_back(tokens[0]);
	}
	fin.close();
}

std::vector<std::string> Service::getFamilies()
{
	std::sort(this->families.begin(), this->families.end(), [](const std::string& s1, const std::string& s2) {return s1 <= s2; });
	return this->families;
}

std::vector<Vegetable> Service::getVegetablesFromFamily(const std::string& family)
{
	std::vector<Vegetable> vegetables;
	for (Vegetable& i : this->vegetables)
	{
		if (i.getFamily() == family)
			vegetables.push_back(i);
	}
	return vegetables;
}

Vegetable Service::getVegetable(std::string& name)
{
	for (auto& v : this->vegetables)
		if (v.getName() == name)
			return v;
	return Vegetable{};
}

void testService()
{
	std::ofstream fout{ "test.txt" };
	fout << "Potato family|Potato|fruit\n";
	fout << "Potato family2|Potato|fruit\n";
	fout.close();
	Service srv{ "test.txt" };

	std::vector<Vegetable> v1, v2;
	v1 = srv.getVegetablesFromFamily("Potato family");
	assert(v1.size() == 1);
	assert(v1[0].to_string() == "Potato fruit");

	std::ofstream fout2{ "test.txt" };
	fout2.close();
}
