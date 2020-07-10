#include "UI.h"

std::vector<std::string> tokenize(std::string string, const char delimiter)
{
	std::vector<std::string> result;

	std::stringstream stringStream{ string };
	std::string token;

	while (std::getline(stringStream, token, delimiter))
		if (token.size() != 0)
		{
			std::stringstream tokenStringStream{ token };
			while (std::getline(tokenStringStream, token, ' '))
				if (token.size() != 0)
					result.push_back(token);
		}

	return result;
}

void UI::startProgram()
{
	while (1)
	{
		std::string userInput, filePath;

		std::vector<std::string> params;

		std::cout << "> ";
		std::getline(std::cin, userInput);

		if (userInput == "exit")
			return;

		if (userInput.size() == 0)
			continue;

		std::vector <std::string> commandParameters{ tokenize(userInput, ',') };
		std::string command = commandParameters[0];

		if (command == "fileLocation")
		{

			commandParameters.erase(commandParameters.begin());

			filePath = "";
			for (const std::string& string : commandParameters)
			{
				filePath += string;
				if (*(string.end() - 1) != '\\')
					filePath += ' ';
			}
			filePath = filePath.substr(0, filePath.size() - 1);
			this->fileLocation(params, filePath);


		}
		if (command == "add")
			this->add(commandParameters);
		if (command == "list" && commandParameters.size() == 2)
		{
			this->listEfficient(commandParameters);
			continue;
		}
		if (command == "list")
			this->list(commandParameters);



	}
}

void UI::add(const std::vector<std::string>& params)
{
	if (params[2] == "Neonatal")
	{
		//HospitalDepartment* department = new NeonatalUnit{ params[0], atoi(params[3].c_str()), atoi(params[4].c_str()),atoi(params[5].c_str()), atof(params[6].c_str())) };
		HospitalDepartment* department = new NeonatalUnit{ params[1], stoi(params[4]), stoi(params[5]), stoi(params[6]), stod(params[7]) };
		this->srv.addDepartment(department);
	}
	if (params[2] == "Surgery")
	{
		HospitalDepartment* department = new Surgery{ params[1], stoi(params[3]), stoi(params[4]) };
		this->srv.addDepartment(department);

	}
}

void UI::list(const std::vector<std::string>& params)
{
	for (auto& department : this->srv.getAllDepartments())
		std::cout << department->toString() << '\n';
}

void UI::listEfficient(const std::vector<std::string>& params)
{
	for (auto& department : this->srv.getAllDepartments())
		if(department->isEfficient() == true)
			std::cout << department->toString() << '\n';

}

void UI::fileLocation(const std::vector<std::string>& params, std::string filePath)
{
	std::string departments;
	for (auto& department : this->srv.getAllDepartments())
		if (department->isEfficient() == true)
			departments += department->toString() + ", " + "efficient" + "\n";
		else
			departments += department->toString() + ", " + "inefficient" + "\n";
	std::ofstream fout{ filePath };
	fout << departments;
	fout.close();

}
