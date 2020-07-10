#pragma once
#include "Repository.h"
#include "Observer.h"

class Service:public Observable
{
private:
	Repository& repo;
public:
	Service(Repository& repo):repo{repo}{}


	std::vector<std::string> getUsers() { return this->repo.getUsers(); }
	std::vector<Question> getQuestions() { return this->repo.getQuestions(); }
	std::vector<Answer> getAnswers() { return this->repo.getAnswers(); }

	std::vector<Question> getSortedQuestions()
	{
		std::vector<Question>questions;
		std::vector<std::pair<Question, int>> pairs;
		for (auto& a : this->repo.getQuestions())
			pairs.push_back(std::make_pair(a, this->repo.getAnswersForQ(a.getId()).size()));

		std::sort(pairs.begin(), pairs.end(), [](std::pair<Question, int>& p1, std::pair<Question, int>& p2) {return p1.second > p2.second; });

		for (auto& p : pairs)
			questions.push_back(p.first);

		return questions;
	}

	std::vector<Answer> getAnswersForQ(int id)
	{
		return this->repo.getAnswersForQ(id);
	}

	Question bestMatching(const std::string& desc)
	{
		return this->repo.bestMatching(desc);
	}

	void addQuestion(const std::string desc, const std::string& name)
	{
		if (desc.size() == 0)
			throw MyException{ "Question is empty" };
		int id = this->repo.getQuestions().size() + 1;
		this->repo.addQuestion(Question{ id,desc,name });
		this->notify();
	}

	void addAnswer(const std::string desc, const std::string& name, int qid)
	{
		if (desc.size() == 0)
			throw MyException{ "Empty desc" };

		int id = this->repo.getAnswers().size();
		this->repo.addAnswer(Answer{ id, qid, name,desc });
		this->notify();
	}
};

