#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

class HospitalDepartment
{
protected:
	std::string hospitalName;
	int numberOfDoctors;
public:
	HospitalDepartment(const std::string& name, int doctors) :hospitalName{ name }, numberOfDoctors{ doctors }{}
	virtual bool isEfficient() = 0;
	virtual std::string to_string()=0;
	virtual ~HospitalDepartment(){}
};

class NeonatalUnit :public HospitalDepartment
{
private:
	int numberOfMothers, numberOfNewBorns;
	double averageGrade;
public:
	NeonatalUnit(const std::string& name, int doctors, int mothers, int newBorns, double avg):HospitalDepartment(name, doctors), numberOfMothers{mothers}, numberOfNewBorns{newBorns}, averageGrade{avg}{}

	bool isEfficient() override {
		return this->averageGrade > 8.5 && this->numberOfNewBorns >= this->numberOfMothers;
	}
	std::string to_string()override;
};

class Surgery :public HospitalDepartment
{
private:
	int numberOfPatients;
public:
	Surgery(const std::string& name, int doctors, int patients):HospitalDepartment(name, doctors), numberOfPatients{patients}{}
		
	bool isEfficient()override {
		return (float)this->numberOfPatients / this->numberOfDoctors >= 2;
	}
	std::string to_string()override {
		return this->hospitalName + " " + std::to_string(this->numberOfDoctors) + " Surgery " + std::to_string(this->numberOfPatients);
	}

};


std::vector<std::string> tokenize(const std::string& string, char delimiter);
std::string double_to_string(double n);
