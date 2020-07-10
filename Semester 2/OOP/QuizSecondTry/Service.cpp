#include "Service.h"

void Service::setScore(std::string name, int score)
{
	this->repo.increaseParticipantScore(name, score);
}

bool Service::correctAnswer(int id, const std::string& answer)
{
	return answer == this->repo.getQuestion(id).getAnswer();
}

int Service::getScore(const std::string& name)
{
	return this->repo.getParticipant(name).getScore();
}
