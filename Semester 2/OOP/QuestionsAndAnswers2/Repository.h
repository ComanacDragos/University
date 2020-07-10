#pragma once
#include "Domain.h"
#include <fstream>
class Repository
{
private:
	std::vector<std::string> users;
	std::vector<Question> questions;
	std::vector<Answer> answers;

	std::string questionsFile, answersFile;

public:
	Repository(const std::string& usersFile, const std::string& QuestionsFile, const std::string& answersFile) :questionsFile{ QuestionsFile }, answersFile{ answersFile }
	{
		std::ifstream fin{ usersFile };
		std::string line;
		while (std::getline(fin, line))
			this->users.push_back(line);
		fin.close();
		fin.open(this->questionsFile, 0);
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->questions.push_back(Question{ stoi(tokens[0]), tokens[1], tokens[2] });
		}
		fin.close();
		fin.open(this->answersFile, 0);
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->answers.push_back(Answer{ stoi(tokens[0]), stoi(tokens[1]), tokens[2],tokens[3], stoi(tokens[4]) });
		}
		fin.close();
	}

	std::vector<std::string> getUsers() { return this->users; }
	std::vector<Question> getQuestions() { return this->questions; }
	std::vector<Answer> getAnswers() { return this->answers; }

	std::vector<Answer> getAnswersForQ(int id) 
	{
		std::vector<Answer> answers;
		for (Answer& a : this->answers)
			if (a.getQId() == id)
				answers.push_back(a);
		return answers;
	}

	Question bestMatching(const std::string& desc)
	{
		int max = 0;
		Question question;

		for (Question& q : this->questions)
		{
			int localMax = 0;
			int i = 0;
			while (i < q.getText().size() && i < desc.size())
			{
				if (q.getText()[i] == desc[i])
					localMax += 1;
				i += 1;
			}
			if (localMax >= max)
			{
				max = localMax;
				question = q;
			}
		}
		return question;
	}

	void addQuestion(const Question& q)
	{
		this->questions.push_back(q);
	}
	void addAnswer(const Answer& a)
	{
		this->answers.push_back(a);
	}

	~Repository()
	{
		std::ofstream foutQ{ this->questionsFile };

		for (Question& q : this->questions)
			foutQ << q.to_string(',') << '\n';
		foutQ.close();

		std::ofstream foutA{ this->answersFile };
		for (Answer& a : this->answers)
			foutA << a.to_string(',') << '\n';
		foutA.close();
	}

};

