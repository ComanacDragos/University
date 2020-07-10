#pragma once
#include "Repository.h"
#include "Observer.h"

class Service : public Observable
{
private:
	Repository<Question> questions{ "Questions.txt" };
	Repository<Participant> participants{ "Participants.txt" };
public:
	Service(){}

	std::vector<Question> getQuestions() { return this->questions.getAll(); }
	std::vector<Participant> getParticipants() { return this->participants.getAll(); }

	
	//Adds a question
	//Throws exception if text is empty or if there is another question with the same id
	void addQuestion(int id, const std::string& text, const std::string& answer, int score);

	Question getQuestion(int id);
};

