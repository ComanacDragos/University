#pragma once
#include "Repository.h"
#include "Observer.h"

class Service : public Observable
{
private:
	Repository& repo;

public:
	Service(Repository& repo):repo{repo}{}

	std::vector<Question> getQuestions() { return repo.getQuestions(); }
	std::vector<Participant> getParticipants() { return repo.getParticipants(); }

	//Adds a question to repository
	void addQuestion(Question& q) { this->repo.storeQuestion(q); this->notify(); }

	Question getQuestion(int id) { return this->repo.getQuestion(id); }

	void setScore(std::string name, int score);

	bool correctAnswer(int id, const std::string& answer);

	int getScore(const std::string& name);
};

