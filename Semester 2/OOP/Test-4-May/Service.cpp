#include "Service.h"

void Service::addDepartment(HospitalDepartment* hospitalDepartment)
{
	this->hospitalsDepartments.push_back(hospitalDepartment);
}

std::vector<HospitalDepartment*> Service::getAllDepartments()
{
	return this->hospitalsDepartments;
}

std::vector<HospitalDepartment*> Service::getAllEfficientDepartments()
{
	std::vector<HospitalDepartment*> efficient;
	for (auto& departments : this->hospitalsDepartments)
		if (departments->isEfficient() == true)
			efficient.push_back(departments);
	return efficient;
}

void Service::writeToFile(const std::string& filename)
{
}

Service::~Service()
{
	for (auto& department : this->hospitalsDepartments)
		delete department;
}
