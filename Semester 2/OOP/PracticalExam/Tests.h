#pragma once
#include "Service.h"
class Tests
{
public:
	Tests()
	{
		testAddStarRepo();
		testAddStarService();
	}

private:

	void testAddStarRepo()
	{
		std::ofstream fout1{ "TestAstronomers.txt" };
		fout1 << "name1,const1\n";
		std::ofstream fout2{ "TestStars.txt" };
		fout2 << "star1,const1,1,1,1\n";
		fout1.close();
		fout2.close();

		Repository repo{ "TestAstronomers.txt", "TestStars.txt" };
		assert(repo.getStars().size() == 1);

		repo.addStar(Star{ "a1","c1",1,1,1 });
		assert(repo.getStars().size() == 2);

		assert(repo.getStars()[1].to_string(' ') == "a1 c1 1 1 1");

		try
		{
			repo.addStar(Star{ "a1","c1",1,1,1 });
			assert(false);
		}
		catch (Exceptions & exc)
		{
			assert(true);
		}
	}

	void testAddStarService()
	{
		std::ofstream fout1{ "TestAstronomers.txt" };
		fout1 << "name1,const1\n";
		std::ofstream fout2{ "TestStars.txt" };
		fout2 << "star1,const1,1,1,1\n";
		fout1.close();
		fout2.close();

		Repository repo{ "TestAstronomers.txt", "TestStars.txt" };
		Service srv{ repo };

		srv.addStar("a1", "c1", 1, 1, 1);
			
		assert(srv.getStars().size() == 2);
		assert(srv.getStars()[1].to_string(' ') == "a1 c1 1 1 1");

		try
		{
			srv.addStar("", "c1", 1, 1, 1);
			assert(false);
		}
		catch (Exceptions & exc)
		{
			assert(true);
		}
		try
		{
			srv.addStar("asd", "c1", 1, 1, 0);
			assert(false);
		}
		catch (Exceptions & exc)
		{
			assert(true);
		}
	}
};

