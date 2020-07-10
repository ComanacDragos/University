#include <iostream>
#include "Set.h"
#include "IceCream.h"
#include <crtdbg.h>


void function2() {
	SmartPointer<string> s1{ new string{ "A" } };
	SmartPointer<string> s2 = s1;
	SmartPointer<string> s3{ new string{ "C" } };
	Set<SmartPointer<string>> set1{};

	try {
		set1 = set1 + s1;
		set1 = set1 + s2;
	}
	catch (std::runtime_error & ex) {
		cout << ex.what(); // prints: "Element already exists!"
	}

	SmartPointer<int> i1{ new int{ 1 } };
	SmartPointer<int> i2{ new int{ 2 } };
	SmartPointer<int> i3{ new int{ 3 } };
	Set<SmartPointer<int>> set2{};
	set2 = set2 + i1;
	set2 = set2 + i2;
	set2 = set2 + i3;
	set2.remove(i1).remove(i3);
	for (auto e : set2)
		cout << *e << ", "; // prints 2,
} // memory is correctly deallocated
int main()
{
	{
	function2();
	create();
	}
	_CrtDumpMemoryLeaks();
}
