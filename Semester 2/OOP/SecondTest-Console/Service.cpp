#include "Service.h"

/*
class Exception :public std::exception
{
private:
	std::string message;
public:
	Exception(std::string mesasge) :message{ mesasge }{}

	const char* what() const throw() override {
		return this->message.c_str();
	}
};
*/
void Service::add(int idMeci, const std::string& echpaAcasa, const std::string numeEchpaDeplasare, int pctAcasa, int pctDeplasare)
{
	std::string errors{ "" };
	if (idMeci < 0)
		errors += "Id negativ\n";
	if (echpaAcasa.size() == 0)
		errors += "Echipa acasa vida\n";
	if (numeEchpaDeplasare.size() == 0)
		errors += "Echipa deplasare vida\n";
	if (pctAcasa < 0)
		errors += "Pct acasa negative\n";
	if (pctDeplasare < 0)
		errors += "Pct deplasare negative\n";

	if (errors.size() != 0)
		throw std::exception{errors.c_str()};

	Meci meci{ idMeci, echpaAcasa, numeEchpaDeplasare, pctAcasa, pctDeplasare };
	this->repo.addMeci(meci);

	int n = this->repo.getEchipe().size();

	for(int i=0;i<n-1;i++)
		for (int j = i + 1; j < n; j++)
		{
			
		}
}

std::vector<Meci> Service::getMeciuri()
{
	return this->repo.getMeciuri();
}
