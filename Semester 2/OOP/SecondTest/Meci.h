#pragma once
#include <string>

class Meci
{
private:
	int idMeci;
	std::string numeEchipaAcasa;
	std::string numeEchipaDeplasare;
	int punctajEchipaAcasa, punctajEchpaDeplasare;

public:
	Meci(int idMeci, const std::string& echpaAcasa, const std::string numeEchpaDeplasare, int pctAcasa, int pctDeplasare) :idMeci{ idMeci }, numeEchipaAcasa{ echpaAcasa }, numeEchipaDeplasare{ numeEchpaDeplasare }, punctajEchipaAcasa{ pctAcasa }, punctajEchpaDeplasare{ pctDeplasare }{}

	int getId() { return this->idMeci; }

	std::string getAcasa();
	std::string getDeplasare();

	std::string to_string();

	bool operator==(Meci meci);
};

