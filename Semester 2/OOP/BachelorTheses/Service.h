#pragma once
#include "Observer.h"
#include "Repository.h"
class Service : public Observable
{
private:
	Repository& repo;
public:
	Service(Repository& repo) :repo{repo}{}

	std::vector<std::string> getTeachers() { return this->repo.getTeachers(); }
	std::vector<Student>getStudents() { return this->repo.getStudents(); }

	std::vector<Student> getStudentsOfTeacher(std::string teacher)
	{
		std::vector<Student> students;
		for (Student& s : this->repo.getStudents())
			if (s.getTeacher() == teacher)
				students.push_back(s);
		return students;
	}

	std::vector<Student> getStudentsByString(std::string string)
	{
		std::vector<Student> students;
		for (Student& s : this->repo.getStudents())
			if (s.getId().find(string) != std::string::npos || s.getName().find(string) != std::string::npos)
				students.push_back(s);
		return students;
	}

	void setStudentTeacher(const std::string& id, const std::string& teacher)
	{
		this->repo.setStudentTeacher(id, teacher);
		this->notify();
	}

	void setMail(const std::string& id, const std::string& mail)
	{
		this->repo.setMail(id, mail);
		this->notify();
	}

	void setThesis(const std::string& id, const std::string& thesis)
	{
		this->repo.setThesis(id, thesis);
		this->notify();
	}

};

