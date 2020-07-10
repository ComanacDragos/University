#pragma once
#include "Domain.h"

class Repository
{
private:
	std::vector<std::string> users;
	std::vector<Question> questions;
	std::vector<Answer> answers;
	
	std::string questionsFile, answersFile;

public:
	Repository(const std::string& userFile, const std::string& questionsFile, const std::string& answersFile):questionsFile{questionsFile}, answersFile{answersFile}
	{
		std::ifstream fin{ userFile };
		std::string line;
		while (std::getline(fin, line))
			this->users.push_back(line);
		fin.close();
		fin.open(questionsFile, 0);
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line,',');
			this->questions.push_back(Question{ stoi(tokens[0]), tokens[1], tokens[2] });
		}
		fin.close();
		fin.open(answersFile, 0);
		while (std::getline(fin, line))
		{
			std::vector<std::string> tokens = tokenize(line, ',');
			this->answers.push_back(Answer{ stoi(tokens[0]), stoi(tokens[1]), tokens[2], tokens[3],stoi(tokens[4]) });
		}
		fin.close();
	}

	std::vector<std::string> getUsers() { return this->users; }
	std::vector<Question> getQuestions() { return this->questions; }
	std::vector<Answer> getAnswers() { return this->answers; }

	void setVotes(int id, int votes)
	{
		for (Answer& a : this->answers)
			if (a.getId() == id)
				a.setVotes(votes);
	}

	void upvote(int id)
	{
		for (Answer& a : this->answers)
			if (a.getId() == id)
				a.upVote();
	}

	void downvote(int id)
	{
		for (Answer& a : this->answers)
			if (a.getId() == id)
				a.downVote();
	}
	void addQuestion(Question& q)
	{
		this->questions.push_back(q);
	}

	void addAnswer(Answer& a)
	{
		this->answers.push_back(a);
	}

	~Repository()
	{
		std::ofstream fout{ this->answersFile };

		for (Answer& a : this->answers)
		{
			fout << std::to_string(a.getId()) << ',' << a.to_string(',')<<'\n';
		}
		fout.close();
		std::ofstream fout2{ this->questionsFile };
		for (Question& q : this->questions)
			fout2 << q.to_string(',') << '\n';
		fout2.close();

	}
};

