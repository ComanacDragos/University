#include <iostream>
#include "Service.h"

using namespace std;
int main()
{
	Repo repo;
	Service service{ repo };
	

	for (auto i:service.getMeciuri())
	cout << i.to_string()<<'\n';

	cout << '\n';

	for (auto i : service.getEchipe())
		cout << i << '\n';
}