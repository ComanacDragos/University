#include "Service.h"

void Service::addIssue(const std::string& description, const std::string& status, const std::string& tester)
{
	if (description.size() == 0)
		throw MyException{ "Description is empty" };
	this->repo.addIssue(Issue{ description, status, tester, " " });
	this->notify();
}
