#pragma once
#include "Domain.h"
#include <fstream>
#include <assert.h>
class Repository
{
private:
	std::string questionsFile, participantsFile;
	std::vector<Question> questions;
	std::vector<Participant> participants;

public:
	Repository(const std::string& qFile,const std::string& pFile);

	void saveQuestions();

	//Adds question to repository
	//Throws exception if the question already exists
	void storeQuestion(Question& q);
	
	//Increasses the score of the participant with the given name by the value of the given score
	void increaseParticipantScore(const std::string& name, int score);

	int getParticipantScore(std::string& name);

	Question getQuestion(int id);
	Participant getParticipant(const std::string& name);

	std::vector<Question> getQuestions() { return this->questions; }
	std::vector<Participant> getParticipants() { return this->participants; }

	~Repository() { this->saveQuestions(); }
};


void testScore();
void testAdd();