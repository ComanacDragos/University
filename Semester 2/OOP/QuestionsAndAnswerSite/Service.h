#pragma once
#include "Repository.h"
#include "Observer.h"
class Service: public Observable
{
private:
	Repository& repo;
public:
	Service(Repository& repo):repo{repo}{}

	std::vector<std::string> getUsers() { return this->repo.getUsers(); }
	std::vector<Question> getQuestions() { return this->repo.getQuestions(); }
	std::vector<Answer> getAnswers() { return this->repo.getAnswers(); }

	std::vector<Answer> getAnswersToQ(int id)
	{
		std::vector<Answer> answers;
		for (Answer& a : this->repo.getAnswers())
			if (a.getQId() == id)
				answers.push_back(a);
		return answers;
	}

	void setVotes(int id, int votes)
	{
		this->repo.setVotes(id, votes);
		this->notify();
	}

	void upvote(int id)
	{
		this->repo.upvote(id);
		this->notify();
	}

	void downvote(int id)
	{
		this->repo.downvote(id);
		this->notify();
	}

	Question searchQuestion(const std::string& string)
	{
		int max = 0;
		Question question = this->getQuestions()[0];

		for (Question& q : this->getQuestions())
		{
			std::string text = q.getText();
			int i = 0;
			int localMax = 0;
			while (i < text.size() && i < string.size())
			{
				if (string[i] == text[i])
					localMax += 1;
				i += 1;
			}
			if (localMax > max)
			{
				max = localMax;
				question = q;
			}
		}
		return question;
	}

	void addQuestion(const std::string& desc, const std::string& name)
	{
		if (desc.size() == 0)
			throw MyException{ "Empty description" };

		int id = this->repo.getQuestions().size()+1;
		this->repo.addQuestion(Question{id, desc, name });
		this->notify();
	}

	void addAnswer(int qid, const std::string& text, const std::string& name)
	{
		if (text.size() == 0)
			throw MyException{ "Empry text" };

		int id = this->repo.getAnswers().size() + 1;
		this->repo.addAnswer(Answer{ id, qid, name,text,0 });
		this->notify();
	}
};

