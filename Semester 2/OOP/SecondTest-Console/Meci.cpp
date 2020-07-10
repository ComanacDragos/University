#include "Meci.h"

std::string Meci::getAcasa()
{
	return this->numeEchipaAcasa;
}

std::string Meci::getDeplasare()
{
	return this->numeEchipaDeplasare;
}

std::string Meci::to_string()
{
	return std::to_string(this->idMeci) + " " + this->numeEchipaAcasa + " " + this->numeEchipaDeplasare + " " + std::to_string(this->punctajEchipaAcasa) + " " + std::to_string(this->punctajEchpaDeplasare);
}

bool Meci::operator==(Meci meci)
{
	return this->idMeci == meci.idMeci;
}
