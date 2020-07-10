#include <memory>
#include <iostream>
#include "Aircraft.h"

#include "UI.h"

int main()
{
	Helicopter h{ 1,"a","a",4,"private" };
	std::cout << h.toString() << '\n';
	Aircraft& a = h;
	std::shared_ptr<Aircraft> p = std::make_shared<Helicopter>(h);
	//std::cout << p->toString();
	
	Repository repo;
	
	repo.add(p);

//	std::vector<std::unique_ptr<Aircraft>>& v = repo.getAircraftsActivity("a");
	for (auto& i : repo.getAircraftsActivity("a"))
	{
		std::cout << "Yes\n";
		
	}
		//Service srv{ repo };

//	srv.addHelicopter(1, "a", "a", 4, "private");
}
