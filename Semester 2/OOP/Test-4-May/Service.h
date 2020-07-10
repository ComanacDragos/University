#pragma once
#include <vector>
#include "HospitalDepartment.h"

class Service
{
private:
	std::vector<HospitalDepartment*> hospitalsDepartments;

public:
	void addDepartment(HospitalDepartment* hospitalDepartment);

	std::vector<HospitalDepartment*> getAllDepartments();

	std::vector<HospitalDepartment*> getAllEfficientDepartments();

	void writeToFile(const std::string& filename);

	~Service();
};

