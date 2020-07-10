#pragma once
#include "Domain.h"

class Repository
{
private:
	std::vector<std::string> teachers;
	std::vector<Student> students;

public:
	Repository(const std::string& teachersFile, const std::string& studentsFile)
	{
		std::ifstream fin{ teachersFile };
		std::string line;
		while (std::getline(fin, line))
			this->teachers.push_back(line);
		fin.close();

		fin.open(studentsFile, 0);
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			if (tokens.size() == 6)
				this->students.push_back(Student{ tokens[0],tokens[1],tokens[2] ,stoi(tokens[3]), tokens[4] ,tokens[5] });
			else
				this->students.push_back(Student{ tokens[0],tokens[1],tokens[2] ,stoi(tokens[3]), tokens[4] ,"" });
		}
		fin.close();
	}

	std::vector<std::string> getTeachers() { return this->teachers; }
	std::vector<Student>getStudents() { return this->students; }

	void setStudentTeacher(const std::string& id, const std::string& teacher)
	{
		for (Student& s : this->students)
			if (s.getId() == id)
			{
				if (s.getTeacher() == "")
					s.setTeacher(teacher);
				else
					break;
			}
	}

	void setMail(const std::string& id, const std::string& mail)
	{
		for (Student& s : this->students)
			if (s.getId() == id)
				s.setEmail(mail);
	}

	void setThesis(const std::string& id, const std::string& thesis)
	{
		for (Student& s : this->students)
			if (s.getId() == id)
				s.setThesis(thesis);
	}
};

