#pragma once
#include <string>

class HospitalDepartment
{
protected:
	std::string hospitalName;
	int numberDoctors;

public:
	HospitalDepartment(const std::string& hospitalName, int numberDoctors);
	virtual bool isEfficient()=0;
	virtual std::string toString();

};

class NeonatalUnit : public HospitalDepartment
{
private:
	int numberMothers;
	int numberNewborns;
public:
	double averageGrade;
	NeonatalUnit(const std::string& hospitalName, int numberDoctors, int numberOfMothers, int newborns, double average);
	bool isEfficient() override;
	std::string toString() override;
};

class Surgery :public HospitalDepartment
{
private:
	int numberPatients;

public:
	Surgery(const std::string& hospitalName, int numberDoctors, int numberPatients);
	bool isEfficient() override;
	std::string toString() override;
};