#include "Repository.h"

void testAddIdeea()
{
	std::ofstream foutI{ "TestIdeeas.txt" };
	std::ofstream foutW{ "TestWriters.txt" };
	foutW.close();
	foutI.close();

	Repository repo{ "TestWriters.txt", "TestIdeeas.txt" };
	Idea i1{ "desc1", "accepted", "c1",1 };
	repo.addIdeea(i1);
	assert(repo.getIdeeas().size() == 1);
	assert(repo.getIdeeas()[0].getDesc() == i1.getDesc());

	assert(repo.getIdeeas()[0].getStatus() == i1.getStatus());

	assert(repo.getIdeeas()[0].getCreator() == i1.getCreator());
	assert(repo.getIdeeas()[0].getAct() == i1.getAct());

	try
	{
		repo.addIdeea(i1);
		assert(false);
	}
	catch (MyException & exc)
	{
		assert(true);
	}
}

void testAcceptIdea()
{
	std::ofstream foutI{ "TestIdeeas.txt" };
	std::ofstream foutW{ "TestWriters.txt" };
	foutW.close();
	foutI.close();

	Repository repo{ "TestWriters.txt", "TestIdeeas.txt" };
	Idea i1{ "desc1", "proposed", "c1",1 };
	repo.addIdeea(i1);

	repo.acceptIdea(i1);

	assert(repo.getIdeeas()[0].getStatus() == "accepted");

}
