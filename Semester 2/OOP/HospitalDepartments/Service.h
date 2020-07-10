#pragma once
#include "HospitalDepartment.h"
#include <memory>
class Service
{
private:
	std::vector<HospitalDepartment*> departments;
public:
	Service(){}
	void addDepartment(HospitalDepartment* department);

	std::vector<HospitalDepartment*> getAllDepartments();

	void writeToFile(const std::string& file);

	std::vector<HospitalDepartment*> getAllEfficientDepartments();

	~Service();
};

