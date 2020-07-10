#include "HospitalDepartment.h"

HospitalDepartment::HospitalDepartment(const std::string& hospitalName, int numberDoctors):hospitalName(hospitalName), numberDoctors(numberDoctors)
{
}

std::string HospitalDepartment::toString()
{
	return this->hospitalName + std::to_string(this->numberDoctors);
}

NeonatalUnit::NeonatalUnit(const std::string& hospitalName, int numberDoctors, int numberOfMothers, int newborns, double average):HospitalDepartment(hospitalName, numberDoctors), numberMothers(numberOfMothers), numberNewborns(newborns), averageGrade(average)
{

}

bool NeonatalUnit::isEfficient()
{
	if (this->averageGrade > 8.5 && this->numberNewborns >= this->numberMothers)
		return true;
	return false;
}

std::string NeonatalUnit::toString()
{
	return this->hospitalName + ",Neonatal Unit, " + std::to_string(this->numberDoctors) + ", " + std::to_string(this->numberMothers) + ", " + std::to_string(this->numberNewborns) + ", " + std::to_string(this->averageGrade);
}

Surgery::Surgery(const std::string& hospitalName, int numberDoctors, int numberPatients):HospitalDepartment(hospitalName, numberDoctors), numberPatients(numberPatients)
{
}

bool Surgery::isEfficient()
{
	if (this->numberPatients / this->numberDoctors >= 2)
		return true;
	return false;
}

std::string Surgery::toString()
{
	return this->hospitalName + ", Surgery, " + std::to_string(this->numberDoctors) + ", " + std::to_string(this->numberPatients);
}

