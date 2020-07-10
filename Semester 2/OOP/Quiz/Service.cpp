#include "Service.h"

void Service::addQuestion(int id, const std::string& text, const std::string& answer, int score)
{
	if (text.size() == 0)
		throw Exceptions{ "Text size is empty" };
	std::vector<Question> questions = this->questions.getAll();

	for (Question& q : questions)
		if (q.getId() == id)
			throw Exceptions{ "Question already exists" };
	this->questions.addElem(Question{ id, text, answer, score });
	this->notify();
	this->questions.saveToFile();
}

Question Service::getQuestion(int id)
{
	Question q{ id, "","",-1 };
	return this->questions.getEl(q);
}

