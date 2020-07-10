#include "Repository.h"

void TestRepo()
{
	std::ofstream fout{ "TestIssues.txt" };
	fout << "issue1,open,name1, ";
	fout.close();
	std::ofstream fout2{ "TestUsers.txt" };
	fout2.close();
	Repository repo{ "TestIssues.txt", "TestUsers.txt" };
	assert(repo.getIssues().size() == 1);
	repo.addIssue(Issue{ "issue2", "closed", "name1", "name2" });
	assert(repo.getIssues().size() == 2);
	assert(repo.getIssue("issue2").to_string(' ') == "issue2 closed name1 name2");

	std::ofstream fout3{ "TestUsers.txt" };
	fout3.close();
	std::ofstream fout4{ "TestIssues.txt" };
	fout4.close();
}

void TestResolve()
{
	std::ofstream fout{ "TestIssues.txt" };
	fout << "issue1,open,name1, ";
	fout.close();
	std::ofstream fout2{ "TestUsers.txt" };
	fout2.close();
	Repository repo{ "TestIssues.txt", "TestUsers.txt" };

	repo.resolveIssue("issue1", "name3");
	assert(repo.getIssue("issue1").to_string(' ') == "issue1 closed name1 name3");

	std::ofstream fout3{ "TestUsers.txt" };
	fout3.close();
	std::ofstream fout4{ "TestIssues.txt" };
	fout4.close();

}
