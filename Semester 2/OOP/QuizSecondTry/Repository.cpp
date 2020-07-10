#include "Repository.h"

Repository::Repository(const std::string& qFile,const std::string& pFile) :questionsFile{ qFile }, participantsFile{ pFile }
{
	std::ifstream finQ{ questionsFile };

	std::string line;
	while (std::getline(finQ, line))
	{
		std::vector<std::string> tokens = tokenize(line, ',');
		this->questions.push_back(Question{ stoi(tokens[0]), tokens[1], tokens[2], stoi(tokens[3]) });
	}
	finQ.close();

	std::ifstream finP{ participantsFile };

	while (std::getline(finP, line))
	{
		std::vector<std::string> tokens = tokenize(line, ',');
		this->participants.push_back(Participant{ tokens[0], stoi(tokens[1]) });
	}
	finP.close();
}

void Repository::saveQuestions()
{
	std::ofstream fout{ questionsFile };
	for (Question& q : this->questions)
	{
		fout << q.to_string() << '\n';
	}
	fout.close();
}

void Repository::storeQuestion(Question& q)
{
	for (Question& question : this->questions)
		if (q.getId() == question.getId())
			throw MyException{ "Question already exists" };
	this->questions.push_back(q);
}

void Repository::increaseParticipantScore(const std::string& name, int score)
{
	for (Participant& p : this->participants)
		if (p.getName() == name)
			p.setScore(score + p.getScore());
}

int Repository::getParticipantScore(std::string& name)
{
	for (Participant& p : this->participants)
		if (p.getName() == name)
			return p.getScore();
}

Question Repository::getQuestion(int id)
{
	for (Question& q : questions)
		if (q.getId() == id)
			return q;
}

Participant Repository::getParticipant(const std::string& name)
{
	for (Participant& p : this->participants)
		if (p.getName() == name)
			return p;
}

void testScore()
{
	std::ofstream fout{ "TestFileP.txt" };
	fout << "name1,0\nname2,0";
	fout.close();
	fout.open("TestFileQ.txt", 1);
	fout.close();
	Repository repo{ "TestFileQ.txt", "TestFileP.txt" };
	repo.increaseParticipantScore("name2", 1);
	assert(repo.getParticipant("name2").getScore() == 1);
	repo.increaseParticipantScore("name2", 1);
	assert(repo.getParticipant("name2").getScore() == 2);

	std::ofstream fout2{ "TestFileP.txt" };
	fout2 << std::endl;
	fout2.close();
	std::ofstream fout3{ "TestFileQ.txt" };
	fout3 << std::endl;
	fout3.close();
}

void testAdd()
{
	std::ofstream fout{ "TestFileP.txt" };
	fout << "name1,0\nname2,0";
	fout.close();
	fout.open("TestFileQ.txt", 0);
	fout.close();
	Repository repo{ "TestFileQ.txt", "TestFileP.txt" };
	
	Question q1{ 1,"t1","a1",3 };
	repo.storeQuestion(q1);
	assert(q1.getId() == repo.getQuestion(1).getId());
	assert(q1.getText() == repo.getQuestion(1).getText());
	assert(q1.getAnswer() == repo.getQuestion(1).getAnswer());
	assert(q1.getScore() == repo.getQuestion(1).getScore());

	try
	{
		repo.storeQuestion(q1);
		assert(false);
	}
	catch (MyException exc)
	{
		assert(true);
	}

	std::ofstream fout2{ "TestFileP.txt" };
	fout2 << std::endl;
	fout2.close();
	std::ofstream fout3{ "TestFileQ.txt" };
	fout3 << std::endl;
	fout3.close();
}

