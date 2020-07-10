#include "Service.h"
#include <assert.h>

void testDelete()
{
	std::ofstream fout{ "test.txt" };
	fout << "name,category,2";
	fout.close();
	Service srv{ "test.txt" };

	assert(srv.getItems().size() == 1);
	srv.deleteItem("name");

	try
	{
		srv.deleteItem("bla");
		assert(false);
	}
	catch (std::exception & exc)
	{
		std::string s = exc.what();
		assert(s == "Item does not exist");
	}

}