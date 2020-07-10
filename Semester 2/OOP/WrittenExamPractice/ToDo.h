#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Activity
{
	friend std::ostream& operator<<(std::ostream&, Activity& a);
private:
	std::string activity, hour;
public:
	Activity(const std::string& a, const std::string& h) :activity{ a }, hour{ h }{}
};

std::ostream& operator<<(std::ostream& o, Activity& a)
{
	o << a.activity << ' ' << a.hour;
	return o;
}


/*
template <typename T>
class IterToDo
{
	friend class ToDo;
private:
	int current;
	ToDo<T>& toDo;

	IterToDo(ToDo<T>& toDo) :toDo{ toDo }
	{
		this->current = 0;
	}

	void operator++() {
		current += 1;
	}

	typename T operator*() {
		return this->toDo.elems[this->current];
	}

	bool operator !=(IterToDo<T>& iter) {
		return this->current != iter.current;
	}

	void setLast() {
		this->current = toDo.elems.size();
	}
};
*/

template <typename T>
class ToDo
{
private:
	std::vector<T> elems;

public:

	typename std::vector<T>::iterator begin() { return this->elems.begin(); }
	typename std::vector<T>::iterator end() { return this->elems.end(); }

	void operator+=(T& a) {
		elems.insert(this->elems.begin(), a);
	}

	void reversePrint(std::ostream& o)
	{
		auto it = this->elems.end();
		while (it != this->elems.begin())
		{
			it--;
			o << *it<<'\n';
		}

	}
};

void ToDoList()
{
	ToDo<Activity> toDo{};
	Activity tiff{ "go to TIFF movie", "20:00" };
	toDo += tiff;
	Activity project{ "Present project","09.20" };
	toDo += project;

	for (auto a : toDo)
		std::cout << a << '\n';

	toDo.reversePrint(std::cout);

}

