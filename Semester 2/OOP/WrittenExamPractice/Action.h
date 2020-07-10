#pragma once
#include <string>
#include <vector>
#include <iostream>

/*
class Action
{
public:
	virtual void execute()=0;

	virtual ~Action(){}
};

class CreateAction: public Action
{
public:
	virtual void execute()override {
		std::cout << "Create file\n";
	}
};

class ExitAction : public Action
{
public:
	virtual void execute()override {
		std::cout << "Exit application\n";
	}
};

class MenuItem
{
private:
	Action* action;
	std::string text;
public:
	MenuItem(const std::string& text, Action* action=nullptr):text{text}, action{action}{}

	virtual void print()
	{
		std::cout << this->text<<'\n';
	}

	virtual void clicked()
	{
		std::cout << this->text << ' ';
		if (this->action != nullptr)
			this->action->execute();
		else
			std::cout << '\n';
	}
	virtual ~MenuItem()
	{
		if (this->action != nullptr)
			delete action;
	}
};

class Menu : public MenuItem
{
private:
	std::vector<MenuItem*> items;
public:
	Menu(std::string text, Action* action = nullptr) :MenuItem{ text,action } {}

	void add(MenuItem* item) { this->items.push_back(item); }

	virtual void print() override 
	{
		MenuItem::print();
	}

	virtual void clicked()
	{
		MenuItem::print();
		for (MenuItem* i : this->items)
			i->print();
		std::cout << '\n';
	}


	virtual ~Menu()
	{
		for (MenuItem* i : this->items)
			delete i;
	}
};

class MenuBar
{
private:
	std::vector<Menu*> menus;
public:
	void add(Menu* m)
	{
		this->menus.push_back(m);
	}
	void print()
	{
		for (Menu* m : this->menus)
			m->print();
		std::cout << '\n';
	}
	virtual ~MenuBar()
	{
		for (Menu* m : this->menus)
			delete m;
	}
};*/


/*
	{
		MenuBar bar;

		Action* exit = new ExitAction;
		Action* createText = new CreateAction;
		Action* createC = new CreateAction;
		MenuItem* textItem = new MenuItem{ "Text", createText };
		MenuItem* textC = new MenuItem{ "C++", createC };

		Menu* New = new Menu{ "New" };
		Menu* Exit = new Menu{ "Exit" , exit};

		New->add(textItem);
		New->add(textC);

		Menu* File = new Menu{ "File" };
		File->add(New);
		File->add(Exit);

		Menu* About = new Menu{ "About" };

		bar.add(File);
		bar.add(About);

		bar.print();

		File->clicked();
		New->clicked();
		textC->clicked();
		Exit->clicked();


	}
	*/
    