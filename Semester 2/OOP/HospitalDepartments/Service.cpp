#include "Service.h"

void Service::addDepartment(HospitalDepartment* department)
{
	this->departments.push_back(department);
}

std::vector<HospitalDepartment*> Service::getAllDepartments()
{
	return this->departments;
}

void Service::writeToFile(const std::string& file)
{
}

std::vector<HospitalDepartment*> Service::getAllEfficientDepartments()
{
	return this->departments;
}

Service::~Service()
{
	for (HospitalDepartment* d : this->departments)
		delete d;
}
