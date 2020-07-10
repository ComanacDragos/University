#pragma once
#include "Service.h"
#include <assert.h>

class Tests
{
public:
	Tests()
	{
		this->testRemoveTask();
		this->testStartTask();
	}

private:
	void testRemoveTask()
	{
		std::ofstream fout{ "TestProgrammers.txt" };
		std::ofstream fout2{ "TestTasks.txt" };
		fout.close();
		fout2.close();

		Repository repo{ "TestProgrammers,txt", "TestTasks.txt" };
		repo.addTask(Task{ "d","closed",1 });
		
		assert(repo.getTasks().size() == 1);
		repo.removeTask("d");
		assert(repo.getTasks().size() == 0);
	}

	void testStartTask()
	{
		std::ofstream fout{ "TestProgrammers.txt" };
		std::ofstream fout2{ "TestTasks.txt" };
		fout.close();
		fout2.close();

		Repository repo{ "TestProgrammers,txt", "TestTasks.txt" };
		Service srv{ repo };

		srv.addTask("desc", "open");
		assert(srv.getTasks()[0].getDesc() == "desc");
		assert(srv.getTasks()[0].getStatus() == "open");
		assert(srv.getTasks()[0].getId() == -1);

		srv.startTask("desc", "open", 1);

		assert(srv.getTasks()[0].getDesc() == "desc");
		assert(srv.getTasks()[0].getStatus() == "inProgress");
		assert(srv.getTasks()[0].getId() == 1);

		try
		{
			srv.startTask("", "closed", 3);
			assert(false);
		}
		catch (MyException & exc)
		{
			assert(true);
		}

	}
};

